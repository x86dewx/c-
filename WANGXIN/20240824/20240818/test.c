#include<head.h>
   

int main(void)
{
    printf("\033[2J");
    printf("\033[9;85H");
    printf("\033[47;30m");
    for(int i = 0 ;i < 25;++i)
    {
            printf("-");
    }
    printf("\033[0m");
    
    printf("\033[10;86H");
    printf("\033[47;30m");
            printf("HHHHHHHHHHHHHHHHHHHHHHH");
    printf("\033[0m");
    printf("\033[40;0H");
    return 0;
}
