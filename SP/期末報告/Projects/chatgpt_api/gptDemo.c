#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "leoJSON.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>

#define SMAX 80
// #include "cJSON.h"
#define write_callback_state_start_response     0
#define write_callback_state_continue_response  1
#define write_callback_state_end_response       2
char *openai_key="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";
char content_end[1024*128];
char global_response[1024*128];
int  global_response_offset=0;
static int write_callback_state = write_callback_state_end_response;
size_t write_callback_chat(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    static int times=0;
    size_t response_size = size * nmemb;
    char *response = malloc(response_size + 1);
    strncpy(response, ptr, response_size);
    response[response_size] = '\0';
    leoJSON_ITEM endSingal;
    if( strstr(response,(char*)"finish_reason")!=NULL )//find_item_with_label_str(response,(char*)"finish_reason",&endSingal))
    {
        memcpy(global_response+global_response_offset,ptr,response_size);
        global_response_offset+=response_size;
        write_callback_state = write_callback_state_end_response;
        {
            global_response[global_response_offset] = '\0';
            leoJSON_ITEM chatFromGPT;
            if(find_item_with_label_str(global_response,(char*)"content",&chatFromGPT))
            {
                leoJSON_ITEM finish_;
                find_item_with_label_str(global_response,(char*)"finish_reason",&finish_);
                chatFromGPT.value_index_e = finish_.label_index_s-6;
                log_leoJSON_item(chatFromGPT,global_response);
                 int content_length = chatFromGPT.value_index_e - chatFromGPT.value_index_s;
                char content[content_length + 1];
                strncpy(content_end, global_response + chatFromGPT.value_index_s, content_length);
                content[content_length] = '\0';
            }
            else
            {
                printf("decode failed!!!\n");
            }        
        }
    }
    else
    {
        memcpy(global_response+global_response_offset,ptr,response_size);
        global_response_offset+=response_size;
    }
    /* print the response data to the console */
    // printf("Response: %s\n", response);
    /* free allocated memory */
    usleep(1000*200);
    free(response);
    return response_size;
}
/* function to send HTTP POST request with json data */

void send_request_chat(char *data)
{
    CURL *curl;
    CURLcode res;

    /* set the API endpoint */
    curl = curl_easy_init();
    if(curl) {
        //step1 set headers{ api key , http url}
        char header_auth[3000];
        sprintf(header_auth,"Authorization: Bearer %s",openai_key);
        /* set request headers */
        struct curl_slist *headers = NULL;
        //step2 set content{ message , model ... api interface}
        char payload_send_char_message [8192];
        char messagesTemplate[]="[{\"role\": \"user\", \"content\": \"%s\"}]";
        char chatRequestTemplate[]="{\"model\":\"%s\",\"messages\":%s}";
        char message[3072];
        char newdata[3072];
        data[strcspn(data, "\n")] = '\0';//這裡卡超級久，因為這裡多了\n跳行造成api有問題
        strcat(data, "。請將句號以前的文字翻譯成英文");
        sprintf(message,messagesTemplate,data);
        //printf("message好像就有問題%s",message);
        sprintf(payload_send_char_message,chatRequestTemplate,"gpt-3.5-turbo",message);
        /* set request data */
       // printf("這裡在搞？%s",payload_send_char_message);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, header_auth);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_send_char_message);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_chat);
        /* perform the request */
        res = curl_easy_perform(curl);
        /* check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        /* cleanup */
        curl_easy_cleanup(curl);
    }
}



struct msg_t {
    long mtype; // type 指定要哪一種消息, 0:取第一個, >0:消息類型為 type 的第一個, <0:消息類型 <=abs(type) 的第一個。
    char mtext[SMAX];
};

int main(int argc, char *argv[]) {
    int id = argv[1][0]-'0';
    int q0 = msgget((key_t) 1235, 0666|IPC_CREAT);
    int q1 = msgget((key_t) 1236, 0666|IPC_CREAT);
    int myQ, yourQ;
    if (id == 0) {
        myQ = q0;
        yourQ = q1;
    } else {
        myQ = q1;
        yourQ = q0;
    }
    struct msg_t msg = {.mtype=1};
    // char msg[SMAX];
    if (fork() == 0) {
        // child: receive message and print
        while (1) {
            msgrcv(yourQ, &msg, SMAX, 0, 0);
            printf("receive: %s\n", msg.mtext);

            // 在這裡進行對 msg.mtext 的修改
            // 例如，將 msg.mtext 轉換為大寫
          /*  for (int i = 0; msg.mtext[i] != '\0'; i++) {
                msg.mtext[i] = toupper(msg.mtext[i]);
            }*/

          //  printf("modified: %s\n", msg.mtext);
             //char src[50], dest[500];
             //strcpy(src,  msg.mtext);
            // strcpy(dest, "請將這段文字翻譯成英文,");
           //strcat(dest, src);

          //  printf("發出去:%s",dest);
           char input[5000];
           strcpy(input, msg.mtext);
            send_request_chat(input);
          //  printf("???",content_end);

            while (write_callback_state != write_callback_state_end_response) {
                usleep(1000); // 將線程休眠一小段時間
            }

       
            global_response_offset = 0;
            memset(global_response, 0, sizeof(global_response));
            write_callback_state = write_callback_state_end_response;
        
        }
    } else {
        // parent: readline and put into myMsg in buf
        while (1) {
            fgets(msg.mtext, SMAX, stdin);
            msgsnd(myQ, &msg, SMAX, 0);
            waitpid(-1, NULL, WNOHANG);
        }
    }
    return 0;
}
