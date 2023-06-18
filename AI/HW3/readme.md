# 八皇后問題

# 參考CHATGPT

# 使用DFS

# 程式碼
```
def is_valid(board, row, col):
    # 檢查是否有皇后
    for i in range(row):
        if board[i] == col:
            return False
    # 檢查左上斜對角是否有皇后
    i, j = row - 1, col - 1
    while i >= 0 and j >= 0:
        if board[i] == j:
            return False
        i -= 1
        j -= 1
    # 檢查右上斜對角是否有皇后
    i, j = row - 1, col + 1
    while i >= 0 and j < len(board):
        if board[i] == j:
            return False
        i -= 1
        j += 1
    return True

def solve_n_queens(n):
    board = [-1] * n  
    solutions = []

    def backtrack(row):
        if row == n:
            solutions.append(board.copy())
        else:
            for col in range(n):
                if is_valid(board, row, col):
                    board[row] = col
                    backtrack(row + 1)
                    board[row] = -1

    backtrack(0)
    return solutions

# 測試
solutions = solve_n_queens(8)
print("八皇后问题的解决方案数量：", len(solutions))
for i, solution in enumerate(solutions):
    print("解决方案", i + 1, ":")
    for row in range(8):
        line = ""
        for col in range(8):
            if solution[row] == col:
                line += "Q "
            else:
                line += ". "
        print(line)
    print()

```