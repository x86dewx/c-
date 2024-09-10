#include<stdio.h>

int main(void)
{
    int n = 1;
    int s[3][3];
    int rows =sizeof(s) /sizeof(s[0]);
    int cols =sizeof(s[0]) / sizeof(s[0][0]);
    for(int i = 0;i < rows;++i)                  // 
    {
        for(int j = 0;j < cols;++j)
        {
            s[i][j] = n;
            ++n;
        }
    }                                            //数组初始化
    int sum1,sum2,sum3,sum4;
    sum3 = 0;
    sum4 = 0;
    int i;
    for(int j = 0;j < cols; ++j)
    {
        int m,n;
        i =rows - 1;
        m = i;
        n = j;
        sum1 = s[i][j];
        --m;
        ++n;
        while(n != j)
        {
            sum1 *= s[m][n];
            --m;
            ++n;
            if(m < 0)
            {

                m += rows;
            }
            if(n > cols - 1)
            {
                n -= cols;
            }
            
        }
        sum3 +=sum1;

    }
    for(int j = 0;j < cols; ++j)
    {
        int m,n;
        i = 0;
        m = i;
        n = j;
        sum2 = s[i][j];
        ++m;
        ++n;
        while(n != j)
        {
            sum2 *= s[m][n];
            ++m;
            ++n;
            if(m > rows - 1)
            {

                m -= rows;
            }
            if(n > cols - 1)
            {
                n -= cols;
            }
        }
        sum4 += sum2;
    }
    printf("行列式的值为%d\n",sum3 - sum4);
    return 0;
}
