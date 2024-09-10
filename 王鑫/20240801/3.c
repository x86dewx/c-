/*************************************************************************
	> File Name: 3.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Thu 01 Aug 2024 05:00:43 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *pNext;
};

void push_front(struct Node *pHead,int n)
{
    struct Node *pNew =malloc(sizeof(struct Node));
    pNew->pNext =pHead->pNext;
    pHead->pNext =pNew;
    pNew->data = n;
}
int size(struct Node *pHead)
{
    struct Node *p =pHead->pNext;
    int counter = 0;
    while(p != NULL)
    {
        ++counter;
        p =p->pNext;
    }
    return counter;
}

int isEmpty(struct Node *pHead)
{
    struct Node *p =pHead->pNext;
    int counter = 0;
    while(p != NULL)
    {
        ++counter;
        p =p->pNext;
    }
    return counter == 0;
}

void printlist(struct Node *pHead)
{
    struct Node *p =pHead->pNext;
    while(p != NULL)
    {
        printf("%d\n",p->data);
        p =p->pNext;
    }
}

void push_back(struct Node *pHead,int n)
{
    if(isEmpty(pHead))
    {
        push_front(pHead,n);
    }
    else
    {
        struct Node *p = pHead->pNext;
        struct Node *pNew =malloc(sizeof(struct Node));
        while(p->pNext != NULL)
        {
            p =p->pNext;
        }
        pNew ->pNext =NULL;
        p->pNext =pNew;
        pNew->data = n;
    }
}
void pop_front(struct Node *pHead)
{
    if(!isEmpty(pHead))
    {
        struct Node *p =pHead->pNext;
        pHead->pNext=p->pNext;
        free(p);
    }
}

void pop_back(struct Node *pHead)
{
    if(size(pHead)>= 2)
    {
        struct Node *p =pHead->pNext;
        while(p->pNext->pNext != NULL)
        {
            p =p->pNext;
        }
        free(p->pNext);
        p->pNext =NULL;
    }
    else
    {
        pop_front(pHead);
    }
}

void clear(struct Node *pHead)
{
    while(!isEmpty(pHead))
    {
        pop_front(pHead);
    }
}


int main(void)
{
    struct Node head = {0,NULL};
    printf("%d\n",size(&head));
    push_back(&head, 1);
    push_back(&head, 2);
    push_back(&head, 3);
    push_back(&head, 4);
    pop_front(&head);
    pop_back(&head);
    clear(&head);
    printf("%d\n",size(&head));
    printlist(&head);
    return 0;
}
