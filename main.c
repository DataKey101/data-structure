#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<windows.h>
#define MAX_SIZE 100 // 定义栈的最大容量
#define EOW 10
#define COL 10
// 定义颜色常量
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_WHITE 15
// 定义位置结构
typedef struct {
    int row;
    int col;
} position;

// 定义栈结构
typedef struct {
    position data[MAX_SIZE]; // 存储栈元素的数组
    int top; // 栈顶指针，指向栈顶元素
} Stack;

// 初始化栈
void initializeStack(Stack* s) {
    s->top = -1; // 初始化栈顶指针为-1，表示栈为空
}

// 检查栈是否为空
bool StackEmpty(Stack* s) {
    return s->top == -1;
}

// 检查栈是否已满
bool StackFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

// 入栈操作
bool push(Stack* s, position value) {
    if (StackFull(s)) {
        printf("栈满了，不能压入元素！\n");
        return false;
    }
    s->data[++s->top] = value; // 先移动栈顶指针，然后添加新元素
    return true;
}

// 出栈操作
bool pop(Stack* s, position* value) {
    if (StackEmpty(s)) {
        //printf("栈空了，不能弹出元素了\n");
        return false;
    }
    *value = s->data[s->top--]; // 先取出栈顶元素，然后移动栈顶指针
    return true;
}

// 获取栈顶元素
bool peek(Stack* s, position* value) {
    if (StackEmpty(s)) {
        printf("栈空了，不存在元素\n");
        return false;
    }
    *value = s->data[s->top];
    return true;
}

// 初始化位置为起点
void initializePosition(position* here) {
    here->row = 1;
    here->col = 1;
}

// 走过的位置封锁
void closePosition(position* past, int maze[][10]) {
    maze[past->row][past->col] = 1;
}

// 重新打开原位置
void startPosition(position* here, int maze[][10]) {
    maze[here->row][here->col] = 0;
}

// 移动方向
bool moveDirection(position* here, int maze[][10]) {
    if (maze[here->row + 1][here->col] == 0) {
        here->row++;
        return true;
    }// 向下移动
    else if (maze[here->row - 1][here->col] == 0) {
        here->row--;
        return true;
    }// 向上移动
    else if (maze[here->row][here->col + 1] == 0) {
        here->col++;
        return true;
    }// 向右移动
    else if (maze[here->row][here->col - 1] == 0) {
        here->col--;
        return true;
    }// 向左移动
    else {
        return false;
    }
}

// 主要程序，找到回去的路
void findWay(position* here, position* past, int maze[][10], Stack* path) {
    *past = *here;
    while (here->row != 8 || here->col != 8) {
        if (moveDirection(here, maze)) {      //如果可以移动的话
            closePosition(past, maze);   //将上一个位置堵住
            push(path, *past);   //将走过的位置压栈
            *past = *here;   //初始化两个位置
        }
        else {
            closePosition(past, maze);   //如果不能走，将该位置堵住不走
            position temp;
            if (pop(path, &temp)) {   //上一个位置出栈，回退重新走
                *here = temp;   
                startPosition(here, maze);   //上一个位置打开
                *past = *here;  //初始化
            }
            else {
                printf("抱歉！老鼠走不出迷宫了\n");
                break;
            }
        }
    }
}
//迷宫 0     
void printPath(Stack* path, position* here) {
    Stack Result;
    initializeStack(&Result);
    if (!StackEmpty(path)) {
        printf("老鼠可以走出迷宫，其中一条迷宫老鼠的路径为：\n");
        while (!StackEmpty(path)) {
            position temp;
            pop(path, &temp);
            push(&Result, temp);
        }
        while (!StackEmpty(&Result)) {
            position temp;
            pop(&Result, &temp);
            printf("(%d,%d) ", temp.row, temp.col);
        }
    }
}
void start(char m, int* row, int* col) {
    switch (m) {
    case 'A':
        (*col)--;
        break;
    case 'D':
        (*col)++;
        break;
    case 'W':
        (*row)--;
        break;
    case 'S':
        (*row)++;
        break;
    default:
        break;
    }
}

void input() {

}
// 设置控制台文本颜色
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    char m = 'm';
    int n;
    int row = 1, col = 2;
    // 创建迷宫
    int maze[10][10] = {
        1,1,1,1,1,1,1,1,1,1,
        1,0,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,0,1,
        1,1,1,1,1,1,1,1,1,1,
    };
    
    
    
    
    
    
    while (m != 'Q') {
        system("cls");
        printf("你现在正在给(%d,%d)创建元素\n", row, col);

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == row && j == col) {
                    setColor(COLOR_RED); // 突出显示当前位置
                    printf("X ");
                    setColor(COLOR_WHITE); // 恢复默认颜色
                }
                else {
                    printf("%d ", maze[i][j]);
                }
            }
            printf("\n");
        }
        printf("请输入你要创建的元素(0-路径，1-障碍物):");
        scanf_s(" %d", &n);
        maze[row][col] = n;
        for (int i = 0; i < 10; i++) {
            maze[0][i] = 1;
            maze[9][i] = 1;
            maze[i][0] = 1;
            maze[i][9] = 1;
        }
        maze[1][1] = 0;
        maze[8][8] = 0;
        system("cls");
        printf("你现在正在给(%d,%d)创建元素\n", row, col);

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == row && j == col) {
                    setColor(COLOR_RED); // 突出显示当前位置
                    printf("%d ",maze[i][j]);
                    setColor(COLOR_WHITE); // 恢复默认颜色
                }
                else {
                    printf("%d ", maze[i][j]);
                }
            }
            printf("\n");
        }
        printf("现在请输入移动方向(A-左,D-右,W-上,S-下,Q-结束):");
        scanf_s(" %c", &m); // 注意前面的空格，用于忽略换行符
        start(m, &row, &col);
    }






    // 创建一个栈表示走过的路径
    Stack path;
    initializeStack(&path);
    // 创建当前位置和下一位置
    position here;
    initializePosition(&here);
    position past;
    initializePosition(&past);

    
    
    
    //打印最终结果
    system("cls");
    printf("您构建的最终迷宫为:\n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (maze[i][j]==0) {
                setColor(COLOR_RED); // 突出显示当前位置
                printf("%d ",maze[i][j]);
                setColor(COLOR_WHITE); // 恢复默认颜色
            }
            else {
                printf("%d ", maze[i][j]);
            }
        }
        printf("\n");
    }
    findWay(&here, &past, maze, &path);
    printPath(&path, &here);

    return 0;
}