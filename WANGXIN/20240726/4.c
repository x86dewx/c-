#include<stdio.h>

int front(int s[][3],int rows)
{
    int i = 0;
    int sum = 0;
    for(i = 0;i < rows;++i)
    {
        sum += s[i][i];
    }
    return sum;
}

int back(int s[][3],int rows)
{
    int i = 0;
    int sum = 0;
    for(i = 0;i < rows;++i)
    {
        sum += s[rows - 1 -i][i];
    }
    return sum;
}

int main(void)
{
    int s[3][3] = {1,2,3,4,5,6,7,8,9};
    int rews =sizeof(s) /sizeof(s[0]);
    int a =front(s,rews);
    int b =back(s,rews);
    printf("%d\n",a + b);
    return 0;
}
