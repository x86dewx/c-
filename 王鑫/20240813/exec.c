#include<stdio.h>
#include<unistd.h>
extern char **environ;
/*
int main(int argc, char *argv[])
{
    execl("/bin/ls","ls","-l",".",NULL);
    return 0;
}
*/


int main(int argc, char *argv[])
{
    execle("./myenv","myenv",NULL,environ);
    return 0;
}
