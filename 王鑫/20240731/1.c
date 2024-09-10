/*************************************************************************
	> File Name: 1.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Wed 31 Jul 2024 10:56:22 AM CST
 ************************************************************************/

#include<stdio.h>




void printfArray2D(int (*a)[4],int rows)
{
    for(int i = 0;i < rows;++i)
    {
        for(int j = 0;j < 4;++j)
        {
            printf("%-3d",*(*(a + i) + j));
        }
        puts("");
    }
}

void advArray2D(int (*a)[4],int rows,float *result)
{
    for(int i = 0;i < rows;++i)
    {
        int sum = 0;
        for(int j = 0;j < 4;++j)
        {
            sum +=*(*(a + i) +j);
        }
        *(result + i) = sum / 4.0;
    }
}




int main(void)
{
    int a[][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int rows =sizeof(a) /sizeof(a[0]);
    float result[rows];
    advArray2D(a,rows,result);
    for(int i = 0;i < rows;++i)
    {
        printf("%f ",*(result + i));
    }
    puts("");
    printfArray2D(a,rows);
    return 0;
}
