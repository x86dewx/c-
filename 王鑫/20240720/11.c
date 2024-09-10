#include<stdio.h>

int main(void)
{
    int i,l=0;
    for (i = 1;i <= 4;++i)
    {
        int j;
        for(j = 1;j <= 4;++j)
        {
            int k;
            
            if(i != j)
            {
                for(k = 1;k <= 4;++k)
                {
                    
                    if(i != k && j!=k)
                    {
                        ++l;
                        printf("%d,",i*100+j*10+k);
                    }
                }
            }
        }
    }

    printf("\b \n");
    printf("组合个数为%d\n",l);
    return 0;
}
