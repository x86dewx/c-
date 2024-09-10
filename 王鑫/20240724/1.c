#include<stdio.h>
#include<string.h>
#if 0
int main(void)
{
    int s[3][4];
    int i,j,sum = 0,k = 1;
    for(i = 0;i < 3;++i)
    {
        for(j = 0;j < 4;++j)
        {
            s[i][j] = k++;
        }
    }
    
    for( i = 0;i < 3;++i)
    {
        for(j = 0;j < 4;++j)
        {
            sum += s[i][j];
        }
    }
    printf("%d\n",sum);
    return 0;
}


int main(void)                  //计算边框元素的和
{
    int s[3][4];
    int i,j,sum = 0,k = 1;
    int rows = sizeof(s) /sizeof(s[0]);
    int cols = sizeof(s[0]) / sizeof(s[0][0]);
    for(i = 0;i < rows;++i)
    {
        for(j = 0;j < cols;++j)
        {
            s[i][j] = k++;
        }
    }
    for(i = 0;i < rows;++i)
    {
        for(j = 0;j < cols;++j)
        {
            if(i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
            {
                sum +=s[i][j];
            }
        }
    }
    printf("%d\n",sum);
    return 0;
}



int main(void)
{
    int s[3][4];
    int i,j,sum = 0,k = 1;
    int rows = sizeof(s) /sizeof(s[0]);
    int cols = sizeof(s[0]) / sizeof(s[0][0]);
    for(i = 0;i < rows;++i)
    {
        for(j = 0;j < cols;++j)
        {
            s[i][j] = k++;
        }
    }
    for(i = 0;i < rows;++i)
    {
        for(j = 0;j < cols / 2;++j)
        {
            int t;
            t = s[i][j];
            s[i][j] = s[i][cols - 1 - i];
            s[i][cols - 1 - i] = t;
        }

    }
    
    for(i = 0;i < rows;++i)
    {
        for(j = 0;j < cols;++j)
        {
            printf("%2d ",s[i][j]);
        }
        printf("\n");
    }

    return 0;
}
#endif

int main(void)
{
    int a[3][3] = {0};
    int i = 0;
    int j = 1;
    a[i][j] = 1;
    int n = 1;
    int rows = sizeof(a) /sizeof(a[0]);
    int cols = sizeof(a[0]) / sizeof(a[0][0]);
    while( n < 9)                                         //n = 9满足n < 10,但是过程中++n，运算结果为10，写入1-10导致写入内存外
    {
        int m,x;                                         //定义变量名不能重复
        m = i;
        x = j;
        --i;
        ++j;
        if(i<0)
        {
            i +=3;
        }
        if(j>2)
        {
            j-=3;
        }
        if(a[i][j] == 0)
        {
            a[i][j] = ++n;
        }
        else
        {
            i = m;
            j = x;
            ++i;
            if(i<0)
            {
                i +=3;
            }                                       //改
            a[i][j] = ++n;
        }

        
    }
    for(i = 0;i < rows;++i)
    {
        for(j = 0;j < cols;++j)
        {
            printf("%2d ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}

#if 0
int main(void)
{
    char s[][100] = {"Hello","World","China","America"};
    int rows = sizeof(s) /sizeof(s[0]);
    int i;
    char max[100];
    strcpy(max,s[0]);
    for(i = 1;i < rows;++i)
    {
        if(strcmp(max,s[i])  < 0)                  //二维数组字符串比较
        {
            strcpy(max,s[i]);

        }
    }
    puts(max);
    return 0;
}

int main(void)
{
    char s[][100] = {"Hello","World","China","America"};
    int rows = sizeof(s) /sizeof(s[0]);
    int cols = sizeof(s[0]) / sizeof(s[0][0]);
    int i;
    for(i = 0;i < rows / 2;++i)
    {
        char t[100];
        strcpy(t,s[i]);
        strcpy(s[i],s[rows - 1-i]);
        strcpy(s[rows -1 -i],t);
    }

    for(i = 0; i < rows;++i)                  //字符串间的翻转
    {
        puts(s[i]);
    }
    
    return 0;
}
#endif
#if 0
int main(void)
{
    char s[][100] = {"Hello","World","China","America"};
    int rows = sizeof(s) /sizeof(s[0]);
    int cols = sizeof(s[0]) / sizeof(s[0][0]);
    int i,j;
    for(i = 0;i<rows - 1;++i)
    {
        int j;
        for(j = i+1;j<rows;++j)
        {
            if(strcmp(s[i],s[j])>0)
            {
                char t[100];
                strcpy(t,s[i]);
                strcpy(s[i],s[j]);                //二维数组中字符串比较
                strcpy(s[j],t);
            }
        }
    }
    char n[100];
    gets(n);
    int begin = 0,end =rows -1,mid;
    while(begin <= end)
    {
        mid = (begin+ end) / 2;
        if(strcmp(s[mid],n)>0)
        {
            end =mid -1;                          //二维数组字符串查找
        }
        else if(strcmp(s[mid],n)<0)
        {
            begin = mid +1;
        }
        else
        {
            break;
        }
    }
    if(begin <= end)
    {
        printf("found\n");
    }
    else
    {
        printf("Not found\n");
    }
    return 0;
}
#endif
