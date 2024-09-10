#include<stdio.h>
#include<unistd.h>

extern char **environ;

int main(int argc, char *argv[])
{
    int i =0;
    while(environ[i] != NULL)
    {
        printf("environ[%d] = %s\n",i,environ[i]);
        ++i;
    }
    
    return 0;
}
