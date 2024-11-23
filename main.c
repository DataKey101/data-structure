#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<windows.h>
#define MAX_SIZE 100 // ����ջ���������
#define EOW 10
#define COL 10
// ������ɫ����
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_WHITE 15
// ����λ�ýṹ
typedef struct {
    int row;
    int col;
} position;

// ����ջ�ṹ
typedef struct {
    position data[MAX_SIZE]; // �洢ջԪ�ص�����
    int top; // ջ��ָ�룬ָ��ջ��Ԫ��
} Stack;

// ��ʼ��ջ
void initializeStack(Stack* s) {
    s->top = -1; // ��ʼ��ջ��ָ��Ϊ-1����ʾջΪ��
}

// ���ջ�Ƿ�Ϊ��
bool StackEmpty(Stack* s) {
    return s->top == -1;
}

// ���ջ�Ƿ�����
bool StackFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

// ��ջ����
bool push(Stack* s, position value) {
    if (StackFull(s)) {
        printf("ջ���ˣ�����ѹ��Ԫ�أ�\n");
        return false;
    }
    s->data[++s->top] = value; // ���ƶ�ջ��ָ�룬Ȼ�������Ԫ��
    return true;
}

// ��ջ����
bool pop(Stack* s, position* value) {
    if (StackEmpty(s)) {
        //printf("ջ���ˣ����ܵ���Ԫ����\n");
        return false;
    }
    *value = s->data[s->top--]; // ��ȡ��ջ��Ԫ�أ�Ȼ���ƶ�ջ��ָ��
    return true;
}

// ��ȡջ��Ԫ��
bool peek(Stack* s, position* value) {
    if (StackEmpty(s)) {
        printf("ջ���ˣ�������Ԫ��\n");
        return false;
    }
    *value = s->data[s->top];
    return true;
}

// ��ʼ��λ��Ϊ���
void initializePosition(position* here) {
    here->row = 1;
    here->col = 1;
}

// �߹���λ�÷���
void closePosition(position* past, int maze[][10]) {
    maze[past->row][past->col] = 1;
}

// ���´�ԭλ��
void startPosition(position* here, int maze[][10]) {
    maze[here->row][here->col] = 0;
}

// �ƶ�����
bool moveDirection(position* here, int maze[][10]) {
    if (maze[here->row + 1][here->col] == 0) {
        here->row++;
        return true;
    }// �����ƶ�
    else if (maze[here->row - 1][here->col] == 0) {
        here->row--;
        return true;
    }// �����ƶ�
    else if (maze[here->row][here->col + 1] == 0) {
        here->col++;
        return true;
    }// �����ƶ�
    else if (maze[here->row][here->col - 1] == 0) {
        here->col--;
        return true;
    }// �����ƶ�
    else {
        return false;
    }
}

// ��Ҫ�����ҵ���ȥ��·
void findWay(position* here, position* past, int maze[][10], Stack* path) {
    *past = *here;
    while (here->row != 8 || here->col != 8) {
        if (moveDirection(here, maze)) {      //��������ƶ��Ļ�
            closePosition(past, maze);   //����һ��λ�ö�ס
            push(path, *past);   //���߹���λ��ѹջ
            *past = *here;   //��ʼ������λ��
        }
        else {
            closePosition(past, maze);   //��������ߣ�����λ�ö�ס����
            position temp;
            if (pop(path, &temp)) {   //��һ��λ�ó�ջ������������
                *here = temp;   
                startPosition(here, maze);   //��һ��λ�ô�
                *past = *here;  //��ʼ��
            }
            else {
                printf("��Ǹ�������߲����Թ���\n");
                break;
            }
        }
    }
}
//�Թ� 0     
void printPath(Stack* path, position* here) {
    Stack Result;
    initializeStack(&Result);
    if (!StackEmpty(path)) {
        printf("��������߳��Թ�������һ���Թ������·��Ϊ��\n");
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
// ���ÿ���̨�ı���ɫ
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    char m = 'm';
    int n;
    int row = 1, col = 2;
    // �����Թ�
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
        printf("���������ڸ�(%d,%d)����Ԫ��\n", row, col);

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == row && j == col) {
                    setColor(COLOR_RED); // ͻ����ʾ��ǰλ��
                    printf("X ");
                    setColor(COLOR_WHITE); // �ָ�Ĭ����ɫ
                }
                else {
                    printf("%d ", maze[i][j]);
                }
            }
            printf("\n");
        }
        printf("��������Ҫ������Ԫ��(0-·����1-�ϰ���):");
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
        printf("���������ڸ�(%d,%d)����Ԫ��\n", row, col);

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == row && j == col) {
                    setColor(COLOR_RED); // ͻ����ʾ��ǰλ��
                    printf("%d ",maze[i][j]);
                    setColor(COLOR_WHITE); // �ָ�Ĭ����ɫ
                }
                else {
                    printf("%d ", maze[i][j]);
                }
            }
            printf("\n");
        }
        printf("�����������ƶ�����(A-��,D-��,W-��,S-��,Q-����):");
        scanf_s(" %c", &m); // ע��ǰ��Ŀո����ں��Ի��з�
        start(m, &row, &col);
    }






    // ����һ��ջ��ʾ�߹���·��
    Stack path;
    initializeStack(&path);
    // ������ǰλ�ú���һλ��
    position here;
    initializePosition(&here);
    position past;
    initializePosition(&past);

    
    
    
    //��ӡ���ս��
    system("cls");
    printf("�������������Թ�Ϊ:\n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (maze[i][j]==0) {
                setColor(COLOR_RED); // ͻ����ʾ��ǰλ��
                printf("%d ",maze[i][j]);
                setColor(COLOR_WHITE); // �ָ�Ĭ����ɫ
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