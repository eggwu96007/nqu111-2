// c4.c - C in four functions

// char, int, and pointer types
// if, while, return, and expression statements
// just enough features to allow self-compilation and a bit more

// Written by Robert Swierczek

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#define int long long 

char *p, *lp, // current position in source code
     *data;   // data/bss pointer

int *e, *le,  // current position in emitted code
    *id,      // currently parsed identifier
    *sym,     // symbol table (simple list of identifiers)
    tk,       // current token
    ival,     // current token value
    ty,       // current expression type
    loc,      // local variable offset
    line,     // current line number
    src,      // print source and assembly flag
    debug;    // print executed instructions
    pt;   // \t的大小
    pt=10; 

// tokens and classes (operators last and in precedence order)
enum {
  Num = 128, Fun, Sys, Glo, Loc, Id,
  Char, Else, Enum, If, Int, Return, Sizeof, While,
  Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};

// opcodes
enum { LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT };

// types
enum { CHAR, INT, PTR };

// identifier offsets (since we can't create an ident struct)
enum { Tk, Hash, Name, Class, Type, Val, HClass, HType, HVal, Idsz };//Idsz9＊8???

void next()
{
  char *pp;//系統一開始隨便給
//將p記憶體位置的第一個值給tk,所以第一個會讀到c的ascii
  while (tk = *p) {
    printf("讀什麼:%d\n",tk);
    ++p;//指向下一個
    //讀到跳行走這裡
    if (tk == '\n') {
      if (src) {
        printf("%d: %.*s", line, p - lp, lp);
        lp = p;
        while (le < e) {
          printf("%8.4s", &"LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,"
                           "OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
                           "OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT,"[*++le * 5]);
          if (*le <= ADJ) printf(" %d\n", *++le); else printf("\n");
        }
      }
      ++line;
    }
    //如果是讀到# 就一直跳，直到換行為止
    else if (tk == '#') {
      while (*p != 0 && *p != '\n')
      {
        ++p;
      } 
    }
    //讀到字母
    else if ((tk >= 'a' && tk <= 'z') || (tk >= 'A' && tk <= 'Z') || tk == '_') {
      pp = p - 1; //記住前一個記憶體位置

      while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || *p == '_')
      {
        tk = tk * 147 + *p++;//將目前的tk * 147 加上下一個位置的ascii值，直到該單字結束為止
        //ex: c:99,h:104,a:97,r:114
        //((99*147+104)*147+97)*147+114
      }
      
      tk = (tk << 6) + (p - pp);//左位移6格
      id = sym;//id和sym連起來
      //printf("頭id[Tk]%d %d\n",id[Tk],id);//sym每次要的位置都不一樣,最一開始的id[Tk]=0
      
      while (id[Tk]) {//第一次執行不會進來，主要判斷id[Tk]有沒有東西，如果有的話就往下
        printf("目前：id[TK]=%d %d\n",id[Tk]);
         /*memcmp意思
        ptr1：指向第一个内存区域的指针。
        ptr2：指向第二个内存区域的指针。
        num：要比较的字节数。
        */
        if (tk == id[Hash] && !memcmp((char *)id[Name], pp, p - pp))//如果compile的時候有相同的字存在symbol table,就會進來
         {
          printf("讀到了什麼%d 位置：%d\n",id[Tk],id); 
          tk = id[Tk]; 
         return; }
        id = id + Idsz;//+9*8
        printf("下一個:id[Tk] %d %d\n",id[Tk],id);
      }
      id[Name] = (int)pp;//pp丟到id[Name] id位置為x,下一個再丟到x+Idsz,所以不會有重複的問題
      id[Hash] = tk;
      tk = id[Tk] = Id;

      printf("next========\n");
      return;
    }
    //讀到數字
    else if (tk >= '0' && tk <= '9') {
      //將ascii轉成數字，如果讀到9(57),就會57-48=9，得到真正的9出來
      if (ival = tk - '0')
       {
         while (*p >= '0' && *p <= '9') ival = ival * 10 + *p++ - '0'; //10進位沒錯
         }
      else if (*p == 'x' || *p == 'X')//0x多少的時候進來，C語言中0x...代表16進位
       {
        //讀到x後往前(*++p)
        while ((tk = *++p) && ((tk >= '0' && tk <= '9') || (tk >= 'a' && tk <= 'f') || (tk >= 'A' && tk <= 'F')))
          { 
          //例1:ival一開始是0,在讀到數字後，tk值會和15去做二進位and,如果讀到9(57)，就會是 111001&01111 ->1001 =9
          //例2:讀到9以後,下一個又是數字(A)，就會將目前的值做進位，A的ascii和15做and運算，01000001&01111 ->0001=1,如果大於等於A，就會多加9
          ival = ival * 16 + (tk & 15) + (tk >= 'A' ? 9 : 0);
          }
          
      //如果讀到A 等於
      }//BUG
      else {//因為C語言中0開頭代表8進位
         while (*p >= '0' && *p <= '7')
          ival = ival * 8 + *p++ - '0'; 
          }
      tk = Num;//算完後要設成數字
      return;
    }
   //讀到註解或是除法
    else if (tk == '/') {
      if (*p == '/') {//代表讀到註解
        ++p;
        while (*p != 0 && *p != '\n') ++p;
      }
      else {//代表讀到除法
        tk = Div;
        return;
      }
    }
    //讀引號"或是'
    else if (tk == '\'' || tk == '"') {
      pp = data;
      printf("讀到這個會是什麼%s",p);
      while (*p != 0 && *p != tk) {//引號後面不是接怪怪的東西就進來,一直讀到引號結束
        if ((ival = *p++) == '\\')
         {
          if ((ival = *p++) == 'n')
          {
            ival = '\n';
          }
          else if (ival == 't')
           {
            ival =32;
            for(int t=0;t<pt;t++)
            *data++ = ival;
           }
          
        }
        if (tk == '"')
         *data++ = ival;
      }
      ++p;
      if (tk == '"')//如果2個引號都讀完，就會把pp位置存到ival
       ival = (int)pp; 
       else 
       tk = Num;
       printf("pp在這裡%s",pp);
       
      return;
    }
    //  判斷=還是==
    else if (tk == '=')
     {printf("讀到等於=======%d\n",tk);
       if (*p == '=')//== 讀到兩個等於
      { ++p; tk = Eq; }
       else tk = Assign;//= 讀到一個等於
        printf("給了");
        return; }
    else if (tk == '+') { if (*p == '+') { ++p; tk = Inc; } else tk = Add; return; }
    else if (tk == '-')
     { 
      if (*p == '-') 
      { ++p; 
      tk = Dec; 
      } 
      else 
      tk = Sub; 
      return; }
    else if (tk == '!') { if (*p == '=') { ++p; tk = Ne; } return; }
    else if (tk == '<') { if (*p == '=') { ++p; tk = Le; } else if (*p == '<') { ++p; tk = Shl; } else tk = Lt; return; }
    else if (tk == '>') { if (*p == '=') { ++p; tk = Ge; } else if (*p == '>') { ++p; tk = Shr; } else tk = Gt; return; }
    else if (tk == '|') { if (*p == '|') { ++p; tk = Lor; } else tk = Or; return; }
    else if (tk == '&') { if (*p == '&') { ++p; tk = Lan; } else tk = And; return; }
    else if (tk == '^') { tk = Xor; return; }
    else if (tk == '%') { tk = Mod; return; }
    else if (tk == '*') { tk = Mul; return; }
    else if (tk == '[') { tk = Brak; return; }
    else if (tk == '?') { tk = Cond; return; }
    else if (tk == '~' || tk == ';' || tk == '{' || tk == '}' || tk == '(' || tk == ')' || tk == ']' || tk == ',' || tk == ':')
     return;
     printf("\n讀完\n");
  }
  printf("next end============\n");
}

void expr(int lev)
{
  printf("進來之後的tk應該一樣是133%d",tk);//因為讀printf內容並沒有動到tk,目前tk還在printf
  int t, *d;

  if (!tk) { printf("%d: unexpected eof in expression\n", line); exit(-1); }
  else if (tk == Num) { *++e = IMM; *++e = ival; next(); ty = INT; }
  else if (tk == '"') {
    //引號讀完之後內容存到e
    *++e = IMM;//e存這要幹嘛
    *++e = ival;//e將存入ival的值放到e中
    next();//引號結束接小逗號,合理
    while (tk == '"') next();
    data = (char *)((int)data + sizeof(int) & -sizeof(int));
     ty = PTR;
  }
  else if (tk == Sizeof) {
    next(); if (tk == '(') next(); else { printf("%d: open paren expected in sizeof\n", line); exit(-1); }
    ty = INT; if (tk == Int) next(); else if (tk == Char) { next(); ty = CHAR; }
    while (tk == Mul) { next(); ty = ty + PTR; }
    if (tk == ')') next(); else { printf("%d: close paren expected in sizeof\n", line); exit(-1); }
    *++e = IMM; *++e = (ty == CHAR) ? sizeof(char) : sizeof(int);
    ty = INT;
  }
  else if (tk == Id) {
    d = id; 
    next();
    if (tk == '(') {
      next();//讀括號內引號中的內容
  //因為這裡遇到引號，所以ival位置改變，同時這裡會存引號內的所有東西
      t = 0;
      while (tk != ')') //如果printf的括號沒結束就繼續讀
      { 
        expr(Assign);
        //如果tk是到引號結束,他就會將引號內容放入e中
        //如果是變數，就會把變數值放入e中
       *++e = PSH;
        ++t;
       if (tk == ',')//引號後面讀到小逗號就會進來
      next();//這裡就讀變數的值
        }
      next();//這裡讀到分號
      if (d[Class] == Sys)
      *++e = d[Val];
      else if (d[Class] == Fun)
       { *++e = JSR; *++e = d[Val]; }
      else
       { printf("%d: bad function call\n", line); exit(-1); }
      if (t) { *++e = ADJ; *++e = t; }
      ty = d[Type];
    }
    //這邊進來是printf引號後讀完到的第二個小逗號
    else if (d[Class] == Num) {
    *++e = IMM;
     *++e = d[Val];
    //這裡把enum的值放進去
    ty = INT; }
    
    else {
      if (d[Class] == Loc)
       { *++e = LEA; *++e = loc - d[Val]; }
      else if (d[Class] == Glo)
       { *++e = IMM; *++e = d[Val]; }
      else
       { printf("%d: undefined variable\n", line); exit(-1); }
      *++e = ((ty = d[Type]) == CHAR) ? LC : LI;
    }
  }
  else if (tk == '(') {
    next();
    if (tk == Int || tk == Char) {
      t = (tk == Int) ? INT : CHAR; next();
      while (tk == Mul) { next(); t = t + PTR; }
      if (tk == ')') next(); else { printf("%d: bad cast\n", line); exit(-1); }
      expr(Inc);
      ty = t;
    }
    else {
      expr(Assign);
      if (tk == ')') next(); else { printf("%d: close paren expected\n", line); exit(-1); }
    }
  }
  else if (tk == Mul) {
    next(); expr(Inc);
    if (ty > INT) ty = ty - PTR; else { printf("%d: bad dereference\n", line); exit(-1); }
    *++e = (ty == CHAR) ? LC : LI;
  }
  else if (tk == And) {
    next(); expr(Inc);
    if (*e == LC || *e == LI) --e; else { printf("%d: bad address-of\n", line); exit(-1); }
    ty = ty + PTR;
  }
  else if (tk == '!') { next(); expr(Inc); *++e = PSH; *++e = IMM; *++e = 0; *++e = EQ; ty = INT; }
  else if (tk == '~') { next(); expr(Inc); *++e = PSH; *++e = IMM; *++e = -1; *++e = XOR; ty = INT; }
  else if (tk == Add) { next(); expr(Inc); ty = INT; }
  else if (tk == Sub) {
    next(); *++e = IMM;
    if (tk == Num) { *++e = -ival; next(); } else { *++e = -1; *++e = PSH; expr(Inc); *++e = MUL; }
    ty = INT;
  }
  else if (tk == Inc || tk == Dec) {
    t = tk; next(); expr(Inc);
    if (*e == LC) { *e = PSH; *++e = LC; }
    else if (*e == LI) { *e = PSH; *++e = LI; }
    else { printf("%d: bad lvalue in pre-increment\n", line); exit(-1); }
    *++e = PSH;
    *++e = IMM; *++e = (ty > PTR) ? sizeof(int) : sizeof(char);
    *++e = (t == Inc) ? ADD : SUB;
    *++e = (ty == CHAR) ? SC : SI;
  }
  else { printf("%d: bad expression\n", line); exit(-1); }
  while (tk >= lev) { // "precedence climbing" or "Top Down Operator Precedence" method
    t = ty;
    if (tk == Assign) {
      next();
      if (*e == LC || *e == LI) *e = PSH; else { printf("%d: bad lvalue in assignment\n", line); exit(-1); }
      expr(Assign); *++e = ((ty = t) == CHAR) ? SC : SI;
    }
    else if (tk == Cond) {
      next();
      *++e = BZ; d = ++e;
      expr(Assign);
      if (tk == ':') next(); else { printf("%d: conditional missing colon\n", line); exit(-1); }
      *d = (int)(e + 3); *++e = JMP; d = ++e;
      expr(Cond);
      *d = (int)(e + 1);
    }
    else if (tk == Lor) { next(); *++e = BNZ; d = ++e; expr(Lan); *d = (int)(e + 1); ty = INT; }
    else if (tk == Lan) { next(); *++e = BZ;  d = ++e; expr(Or);  *d = (int)(e + 1); ty = INT; }
    else if (tk == Or)  { next(); *++e = PSH; expr(Xor); *++e = OR;  ty = INT; }
    else if (tk == Xor) { next(); *++e = PSH; expr(And); *++e = XOR; ty = INT; }
    else if (tk == And) { next(); *++e = PSH; expr(Eq);  *++e = AND; ty = INT; }
    else if (tk == Eq)  { next(); *++e = PSH; expr(Lt);  *++e = EQ;  ty = INT; }
    else if (tk == Ne)  { next(); *++e = PSH; expr(Lt);  *++e = NE;  ty = INT; }
    else if (tk == Lt)  { next(); *++e = PSH; expr(Shl); *++e = LT;  ty = INT; }
    else if (tk == Gt)  { next(); *++e = PSH; expr(Shl); *++e = GT;  ty = INT; }
    else if (tk == Le)  { next(); *++e = PSH; expr(Shl); *++e = LE;  ty = INT; }
    else if (tk == Ge)  { next(); *++e = PSH; expr(Shl); *++e = GE;  ty = INT; }
    else if (tk == Shl) { next(); *++e = PSH; expr(Add); *++e = SHL; ty = INT; }
    else if (tk == Shr) { next(); *++e = PSH; expr(Add); *++e = SHR; ty = INT; }
    else if (tk == Add) {
      next(); *++e = PSH; expr(Mul);
      if ((ty = t) > PTR) { *++e = PSH; *++e = IMM; *++e = sizeof(int); *++e = MUL;  }
      *++e = ADD;
    }
    else if (tk == Sub) {
      next(); *++e = PSH; expr(Mul);
      if (t > PTR && t == ty) { *++e = SUB; *++e = PSH; *++e = IMM; *++e = sizeof(int); *++e = DIV; ty = INT; }
      else if ((ty = t) > PTR) { *++e = PSH; *++e = IMM; *++e = sizeof(int); *++e = MUL; *++e = SUB; }
      else *++e = SUB;
    }
    else if (tk == Mul) { next(); *++e = PSH; expr(Inc); *++e = MUL; ty = INT; }
    else if (tk == Div) { next(); *++e = PSH; expr(Inc); *++e = DIV; ty = INT; }
    else if (tk == Mod) { next(); *++e = PSH; expr(Inc); *++e = MOD; ty = INT; }
    else if (tk == Inc || tk == Dec) {
      if (*e == LC) { *e = PSH; *++e = LC; }
      else if (*e == LI) { *e = PSH; *++e = LI; }
      else { printf("%d: bad lvalue in post-increment\n", line); exit(-1); }
      *++e = PSH; *++e = IMM; *++e = (ty > PTR) ? sizeof(int) : sizeof(char);
      *++e = (tk == Inc) ? ADD : SUB;
      *++e = (ty == CHAR) ? SC : SI;
      *++e = PSH; *++e = IMM; *++e = (ty > PTR) ? sizeof(int) : sizeof(char);
      *++e = (tk == Inc) ? SUB : ADD;
      next();
    }
    else if (tk == Brak) {
      next(); *++e = PSH; expr(Assign);
      if (tk == ']') next(); else { printf("%d: close bracket expected\n", line); exit(-1); }
      if (t > PTR) { *++e = PSH; *++e = IMM; *++e = sizeof(int); *++e = MUL;  }
      else if (t < PTR) { printf("%d: pointer type expected\n", line); exit(-1); }
      *++e = ADD;
      *++e = ((ty = t - PTR) == CHAR) ? LC : LI;
    }
    else { printf("%d: compiler error tk=%d\n", line, tk); exit(-1); }
  }
}

//執行function的函數
void stmt()
{
  int *a, *b;

  if (tk == If) {
    next();
    if (tk == '(') 
    next(); //這裡把printf("")內東西都讀完
    else
     { printf("%d: open paren expected\n", line); exit(-1); }
   // printf("執行expr=======\n");
    expr(Assign);
 //   printf("結束expr=======\n");
    if (tk == ')') next(); else { printf("%d: close paren expected\n", line); exit(-1); }
    *++e = BZ; b = ++e;
    stmt();
    if (tk == Else) {
      *b = (int)(e + 3); *++e = JMP; b = ++e;
      next();
      stmt();
    }
    *b = (int)(e + 1);
  }
  else if (tk == While) {
    next();
    a = e + 1;
    if (tk == '(') next(); else { printf("%d: open paren expected\n", line); exit(-1); }
    expr(Assign);
    if (tk == ')') next(); else { printf("%d: close paren expected\n", line); exit(-1); }
    *++e = BZ; b = ++e;
    stmt();
    *++e = JMP; *++e = (int)a;
    *b = (int)(e + 1);
  }
  else if (tk == Return) {
    next();
    if (tk != ';') expr(Assign);
    *++e = LEV;
    if (tk == ';') next(); else { printf("%d: semicolon expected\n", line); exit(-1); }
  }
  else if (tk == '{') {
    next();
    while (tk != '}') stmt();
    next();
  }
  else if (tk == ';') {
    next();
  }
  else {
    printf("112後面接續的");
    expr(Assign);
    if (tk == ';') next(); else { printf("%d: semicolon expected\n", line); exit(-1); }
  }
}

signed main(signed argc, char **argv) //argc為有多少參數，argv為內容
{
  int fd, bt, ty, poolsz, *idmain;
  int *pc, *sp, *bp, a, cycle; // vm registers
  int i, *t; // temps

  --argc; ++argv;
  if (argc > 0 && **argv == '-' && (*argv)[1] == 's') //讀入s參數
  { src = 1; --argc; ++argv; }
  if (argc > 0 && **argv == '-' && (*argv)[1] == 'd')// 讀入d參數
  { debug = 1; --argc; ++argv; }
  if (argc < 1) //參數有誤
  { printf("usage: c4 [-s] [-d] file ...\n"); return -1; }

  if ((fd = open(*argv, 0)) < 0)//無法開啟檔案
   { printf("could not open(%s)\n", *argv); return -1; }

  poolsz = 256*1024; //給定隨意大小
  if (!(sym = malloc(poolsz))) 
  { printf("could not malloc(%d) symbol area\n", poolsz); return -1; }
  if (!(le = e = malloc(poolsz))) 
  { printf("could not malloc(%d) text area\n", poolsz); return -1; }
  if (!(data = malloc(poolsz))) 
  { printf("could not malloc(%d) data area\n", poolsz); return -1; }
  if (!(sp = malloc(poolsz))) 
  { printf("could not malloc(%d) stack area\n", poolsz); return -1; }
//記憶體配置
  memset(sym,  0, poolsz);
  memset(e,    0, poolsz);
  memset(data, 0, poolsz);

  //  系統一開始會給p的記憶體位置
  p = "char else enum if int return sizeof while "
      "open read close printf malloc free memset memcmp exit void main";
  
  i = Char; 
  //這裡會存Tk,Hash,Name到symbol table
  while (i <= While) //134-141
   { 
    next();
    id[Tk] = i++;
    }
    printf("==========WHILE END=============\n");

   i = OPEN; 
   id=id-Idsz;//-72


  //這裡存Tk(一樣的:133),Hash Name ,Class(一樣的),Type(一樣的),Val
  while (i <= EXIT) 
  { 
  next(); 
  id[Class] = Sys;
  id[Type] = INT;
  id[Val] = i++; 
  
  } // add library to symbol table
printf("==========EXIT END=============\n");

//存void
  next(); 
  id[Tk] = Char; 
  printf("==========void END=============\n");

 //存main
  next();
   idmain = id; //???
printf("==========main END(建立完成)=============\n");
//往後新增的變數，tk會是133，如果設關鍵字為變數，就會有問題

  if (!(lp = p = malloc(poolsz)))//超出記憶體分配
  { printf("could not malloc(%d) source area\n", poolsz);
   return -1; }
  
  if ((i = read(fd, p, poolsz-1)) <= 0)//檔案讀取失敗
  { printf("read() returned %d\n", i);
   return -1; 
   }
  p[i] = 0;//檔案內容最後面放一個0
  close(fd);
//p現在放的是fd的內容
//===============(prog)
  // parse declarations
  line = 1;
  next();//這裡讀
  while (tk) {//開始讀檔案，並放入symbolTable
    printf("新的一行%d %d\n",id,tk);
    bt = INT; // basetype,型態是什麼
    //如果讀到int會進來 通常int後面會配參數或函數
    if (tk == Int)
    {
       next();
      
    } 
    //如果讀到Char會進來
    else if (tk == Char)
     { 
     next(); 
     bt = CHAR; }
   //enum型態讀完
    else if (tk == Enum) {
      next();//執行這個去把下一個內容抓出來
      if (tk != '{') { //enum後面語法錯誤
        printf("%d:bad enum identifier(enum語法錯誤) %d\n", line, tk);
        return -1; 
      }
   
      if (tk == '{') {     
        next();//存變數
        i = 0;
        
        while (tk != '}') {//如果enum沒有結束就會繼續讀
          if (tk != Id)//如果讀到關鍵字就會掛掉(p一開始建的symbolTable關鍵字)
          { 
          printf("%d:bad enum identifier(enum語法錯誤) %d\n", line, tk);
          return -1; 
          }

          next();//存數字
          if (tk == Assign)//如果TK給予了一個很奇怪的值，如rr=a，就會掛掉
           {
            next();
            if (tk != Num) //如果等於後面不是數字就會錯誤
            { printf("%d:enum initializer(賦予奇怪的值)\n", line);
             return -1; }
            i = ival;
            next();
          }
          id[Class] = Num;
          id[Type] = INT;
          id[Val] = i++;
          if (tk == ',')
           next();//存變數
        }
        next();//讀了enum的分號
      }
    }
    //如果沒有讀到分號或}就會一直繼續把該段落讀完
    while (tk != ';' && tk != '}') {
      ty = bt;
      while (tk == Mul)
       { next(); ty = ty + PTR; }
      if (tk != Id)
       { printf("%d: bad global declaration\n", line); return -1; }
      if (id[Class])
       { printf("%d: duplicate global definition\n", line); return -1; }
      next();//讀到main(
      printf("上面next是跑什麼");
      id[Type] = ty;//要記住這個function的型態
      if (tk == '(') { // function //前面一個next會讀到main後面的括號

        id[Class] = Fun;
        id[Val] = (int)(e + 1);//目前這裡放main的function
        //64位元的電腦這裡記憶體位置會跳8,32位元這裡會跳4
        next(); //讀到main()

        i = 0;

        while (tk != ')') {
          ty = INT;
          if (tk == Int) next();
          else if (tk == Char) { next(); ty = CHAR; }
          while (tk == Mul) { next(); ty = ty + PTR; }
          if (tk != Id) { printf("%d: bad parameter declaration\n", line); return -1; }
          if (id[Class] == Loc) { printf("%d: duplicate parameter definition\n", line); return -1; }
          id[HClass] = id[Class]; id[Class] = Loc;
          id[HType]  = id[Type];  id[Type] = ty;
          id[HVal]   = id[Val];   id[Val] = i++;
          next();
          if (tk == ',') next();
        }

        next();//main(){

        if (tk != '{') { printf("%d: bad function definition\n", line); return -1; 
        }
        loc = ++i;//這是什麼
        next();//printf tk=133

        while (tk == Int || tk == Char) {
          printf("133不會進來，看到就有鬼");
          bt = (tk == Int) ? INT : CHAR;
          next();
          while (tk != ';') {
            ty = bt;
            while (tk == Mul) { next(); ty = ty + PTR; }
            if (tk != Id) { printf("%d: bad local declaration\n", line); return -1; }
            if (id[Class] == Loc) { printf("%d: duplicate local definition\n", line); return -1; }
            id[HClass] = id[Class]; id[Class] = Loc;
            id[HType]  = id[Type];  id[Type] = ty;
            id[HVal]   = id[Val];   id[Val] = ++i;
            next();
            if (tk == ',') next();
          }
          next();
        }
        *++e = ENT;//e存這要幹嘛
        *++e = i - loc;//e存這要幹嘛
        printf("e存i-loc%d",i-loc);
        while (tk != '}')
        {
          stmt();//這裡會執行function內的事情
        } 
        *++e = LEV;
        id = sym; // unwind symbol table locals
        while (id[Tk]) {
          if (id[Class] == Loc) {
            id[Class] = id[HClass];
            id[Type] = id[HType];
            id[Val] = id[HVal];
          }
          id = id + Idsz;
        }
      }
      else {
        id[Class] = Glo;
        id[Val] = (int)data;
        data = data + sizeof(int);
      }
      if (tk == ',')
      next();
    }
    next();//enum結束後不會進去while迴圈
    printf("結束了結束了結束了\n");
  }


//==================(編譯結束)
  if (!(pc = (int *)idmain[Val])) 
   { 
    printf("main() not defined\n");
     return -1; }
  if (src) 
  return 0;

  // setup stack
  bp = sp = (int *)((int)sp + poolsz);
  *--sp = EXIT; // call exit if main returns
  *--sp = PSH; t = sp;
  *--sp = argc;
  *--sp = (int)argv;
  *--sp = (int)t;

  // run...
  cycle = 0;
  while (1) {
    i = *pc++;
     ++cycle;
    if (debug) {
      printf("%d> %.4s", cycle,
        &"LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,"
         "OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
         "OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT,"[i * 5]);
      if (i <= ADJ) printf(" %d\n", *pc); else printf("\n");
    }
    if      (i == LEA) a = (int)(bp + *pc++);                             // load local address
    else if (i == IMM) a = *pc++;                                         // load global address or immediate
    else if (i == JMP) pc = (int *)*pc;                                   // jump
    else if (i == JSR) { *--sp = (int)(pc + 1); pc = (int *)*pc; }        // jump to subroutine
    else if (i == BZ)  pc = a ? pc + 1 : (int *)*pc;                      // branch if zero
    else if (i == BNZ) pc = a ? (int *)*pc : pc + 1;                      // branch if not zero
    else if (i == ENT) { *--sp = (int)bp; bp = sp; sp = sp - *pc++; }     // enter subroutine
    else if (i == ADJ) sp = sp + *pc++;                                   // stack adjust
    else if (i == LEV) { sp = bp; bp = (int *)*sp++; pc = (int *)*sp++; } // leave subroutine
    else if (i == LI)  a = *(int *)a;                                     // load int
    else if (i == LC)  a = *(char *)a;                                    // load char
    else if (i == SI)  *(int *)*sp++ = a;                                 // store int
    else if (i == SC)  a = *(char *)*sp++ = a;                            // store char
    else if (i == PSH) *--sp = a;                                         // push

    else if (i == OR)  a = *sp++ |  a;
    else if (i == XOR) a = *sp++ ^  a;
    else if (i == AND) a = *sp++ &  a;
    else if (i == EQ)  a = *sp++ == a;
    else if (i == NE)  a = *sp++ != a;
    else if (i == LT)  a = *sp++ <  a;
    else if (i == GT)  a = *sp++ >  a;
    else if (i == LE)  a = *sp++ <= a;
    else if (i == GE)  a = *sp++ >= a;
    else if (i == SHL) a = *sp++ << a;
    else if (i == SHR) a = *sp++ >> a;
    else if (i == ADD) a = *sp++ +  a;
    else if (i == SUB) a = *sp++ -  a;
    else if (i == MUL) a = *sp++ *  a;
    else if (i == DIV) a = *sp++ /  a;
    else if (i == MOD) a = *sp++ %  a;

    else if (i == OPEN) a = open((char *)sp[1], *sp);
    else if (i == READ) a = read(sp[2], (char *)sp[1], *sp);
    else if (i == CLOS) a = close(*sp);
    else if (i == PRTF) { t = sp + pc[1]; a = printf((char *)t[-1], t[-2], t[-3], t[-4], t[-5], t[-6]); }
    else if (i == MALC) a = (int)malloc(*sp);
    else if (i == FREE) free((void *)*sp);
    else if (i == MSET) a = (int)memset((char *)sp[2], sp[1], *sp);
    else if (i == MCMP) a = memcmp((char *)sp[2], (char *)sp[1], *sp);
    else if (i == EXIT) { printf("exit(%d) cycle = %d\n", *sp, cycle); return *sp; }
    else { printf("unknown instruction = %d! cycle = %d\n", i, cycle); return -1; }
  }
}
