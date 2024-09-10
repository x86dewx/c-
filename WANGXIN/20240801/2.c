/*************************************************************************
	> File Name: 2.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Thu 01 Aug 2024 02:01:28 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Student 
{
    int id;
    float score;
    char name[20];
};


void printStudent(struct Student *a,int len)
{
    for(int i = 0;i < len;++i)
    {
        printf("%d ,%f ,%s\n",(a + i) ->id,(a + i) ->score,(a + i) ->name);
    }
}

void swap(struct Student *a,struct Student *b)
{
    struct Student t;
    t = *a;
    *a = *b;
    *b = t;
}

void reveserStudent(struct Student *a,int len)
{
    for(int i = 0;i < len / 2;++i)
    {
        swap(a + i,a + len - 1 - i);
    }
}

void sortid(struct Student *a,int len)
{
    for(int i = 0;i < len - 1;++i)
    {
        for(int j = i + 1;j < len;++j)
        {
            if(a[i].id >a[j].id)
            swap(a + i,a + j);
        }
    }
}

void sortname(struct Student *a,int len)
{
    for(int i = 0;i < len - 1;++i)
    {
        for(int j = i + 1;j < len;++j)
        {
            if(strcmp((a + i)->name,(a + j)->name) > 0)
            swap(a + i,a + j);
        }
    }
}
int scorecmp(const void *p1,const void *p2)
{
    struct Student *q1 = (struct Student *)p1;
    struct Student *q2 = (struct Student *)p2;
    if(q1 ->score > q2 ->score)
    {
        return 1;
    }
    else if(q1 ->score < q2 ->score)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int namecmp(const void *p1,const void *p2)
{
    struct Student *q1 = (struct Student *)p1;
    struct Student *q2 = (struct Student *)p2;
    return strcmp(q1 -> name,q2 -> name);
}

int idcmp(const void *p1,const void *p2)
{
    struct Student *q1 = (struct Student *)p1;
    struct Student *q2 = (struct Student *)p2;
    if(q1 ->id > q2 ->id)
    {
        return 1;
    }
    else if(q1 ->id < q2 ->id)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void main(void)
{
    struct Student a[3] ={{1,92,"wang"},{2,93,"li"},{3,94,"zhao"}};
    int len = sizeof(a) / sizeof(a[0]);
    //sortid(a,len);
    //sortname(a,len);
    // reveserStudent(a,len);
    qsort(a,len,sizeof(a[0]),namecmp);
    printStudent(a,len);
}
