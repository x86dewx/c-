#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>


int main(int argc, char *argv[])
{
    key_t key =ftok("/",'X');
    if(key < -1)
    {
        perror("key fail");
    }
    printf("key = %d\n",key);
    return 0;
}
