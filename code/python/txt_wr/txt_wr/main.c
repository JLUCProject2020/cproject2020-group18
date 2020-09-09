#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct user_info{
    char name[20];
    char time[6];
    int score;
}User[100];
int Comp1(const void*x, const void*y)
{
    struct user_info xx = *(struct user_info*)x;
    struct user_info yy = *(struct user_info*)y;
    float a = atof(xx.time);
    float b = atof(yy.time);
    if (a != b)
        return a - b;
    else
        return a - b;
}
int Comp2(const void*x, const void*y)
{
    struct user_info xx = *(struct user_info*)x;
    struct user_info yy = *(struct user_info*)y;
    if (strcmp(xx.name, yy.name))
        return strcmp(xx.name, yy.name);
    else
        if (xx.time != yy.time)
            return xx.time - yy.time;
        else
            return xx.time - yy.time;
}
    

int main() {
    FILE* read = fopen("D:\\python_code\\pygamel_v2.0\\ranking.txt", "r+");
    if (NULL == read) {
        return 0;
    }
    User temp;
    int i = 0;
    while (fscanf(read, "%s\t%s\t%d\n", temp[i].name, temp[i].time, &temp[i].score) != EOF) {
        i++;
    }
    fclose(read);
    qsort(temp, i, sizeof(temp[0]), Comp2);
    int index = 1;//下标 
    User b;//存放不重复元素的数组
    b[0] = temp[0];
    int count = 1;
    for (int k = 1; k < i; k++) {
        if (strcmp(temp[k].name, temp[k - 1].name)) {  //如果当前遍历的元素和前一个元素不相等
            b[index++] = temp[k];//存到b中   
            count++;
        }
    }
        
    qsort(b, count, sizeof(b[0]), Comp1);
    FILE* write = fopen("D:\\python_code\\pygamel_v2.0\\ranking_display.txt", "w");
    for (int k = 0; k < count; ++k) {
        char res[31];
        char buff[4];
        itoa(b[k].score, buff, 10);
        for (int i = 0, j = 0; i < 31; ++i) {
            if (i < strlen(b[k].name) && b[k].name[i] != '\0')
                res[i] = b[k].name[i];
            else if (i < 17)
                res[i] = '-';
            else if (i < strlen(b[k].time)+17 && b[k].time[i-17] != '\0')
                res[i] = b[k].time[i-17];
            else if (i < 27)
                res[i] = '-';
            else
                res[i] = buff[j++];
        }
        fprintf(write, "%s\n", res);
    }
    fclose(write);
    return 0;
}