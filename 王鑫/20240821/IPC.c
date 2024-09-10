#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{

	key_t key = ftok("/",'A');

	if (key < 0)
	{
		perror("ftok fail");
		return -1;
	}

	printf("key = %d\n",key);

	int shmid = shmget(key,1024,IPC_CREAT|0666);

	if (shmid < 0)
	{
		perror("shmget fail");
		return -1;
	}

	printf("shmid = %d\n",shmid);
	
	void *p = shmat(shmid,NULL,0);

	if (p == (void *)-1)
	{
		perror("shmat fail\n");
		return -1;
	}

    char a[] ="nihao";
    p = (void *)a;
    printf("%s\n",p);



	return 0;
}


