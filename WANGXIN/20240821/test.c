#include<stdio.h>
#include<math.h>




long long findMaximumNumber(long long k, int x) 
{
    int sum = 0;
    int i = 0;
    int sum1 = 0;
    int j = 0;
    int e = 0;
    int flag = 0;
    
    for(i = 1;;i++)
    {
        sum1 = 0;
        // 1 0 1 0
        for (e = 0, flag = (1 << x-1); flag <= i; flag <<= x)
        {
            if (i & flag)
            {
                sum1 += 1;
            }
        }

#if 0
        //   printf("%d\n" ,j);
        for(int e =j;e >0;e =e - x)
        {
            int q = 1;
            q =q<<e;
            if((i & 1)==1)
            {
                ++sum1;
            }

        }
#endif

        sum = sum +sum1;
        printf("%d\n",sum);
        if(sum ==k)
        {
            return i;
        }
        else if(sum > k)
        {
            return i - 1 ;
        }
    }

    return 0;

}


int main(void)
{
    printf("%lld\n",findMaximumNumber(7,2));
    return 0;
}
