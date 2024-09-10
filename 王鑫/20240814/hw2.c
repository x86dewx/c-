
#include<stdio.h>
#include <pthread.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>

void *a(void *arg)
{
        static char x[] = "nahida";
       // pthread_exit(x);
       sleep(5);
        return x;
}
int main(int argc, char *argv[])
{
    
    pthread_t tid1;
    int ret1 =pthread_create(&tid1,NULL,a,NULL);
    pthread_detach(tid1);
    if(ret1 != 0)
    {
        errno = ret1;
        perror("pthread1 fail");
        return -1;
    }

    sleep(2);
  //  while(1);
   // pthread_cancel(tid1);
   // printf("pthread calcel\n");

   void *p =NULL;
   if( pthread_join(tid1,&p) !=0)
   {
       perror("pthread_join fail\n");
   }
  //  printf("-----main------%s\n",(char*)p);
    return 0;
}
