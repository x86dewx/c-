#include<head.h>

#define MAX_NAME_LENGTH 256
#define MAX_FILES 1024


int isMUsic(char *a)
{
    int i = 0;
    int b = 0;
    while(*(a +i) !='.' && *(a + i) !='\0')
    {
        ++i;
    }
    if(*(a + i) == '\0')
    {
        return 0;
    }
    char buf[100] ={0};
    ++i;
    int j = 0;
    while(a[i] !='\0')
    {
        buf[j] =a[i];
        ++i;
        ++j;
    }
    buf[j] ='\0';
    if(strcmp(buf,"flv") == 0||strcmp(buf,"mp3") == 0||strcmp(buf,"mp4")==0)
    {
        return 1;
    }

    return 0;

}


int findMusic(const char *a,char *s[])
{
    struct dirent *entry;
    DIR* dirp=opendir(a);
    if(dirp ==NULL)
    {
        perror("fail\n");
        return -1;
    }
    int i =0;

    while ((entry = readdir(dirp)) != NULL && i < MAX_FILES) 
    {
        s[i] = (char*)malloc(MAX_NAME_LENGTH);
        if (s[i] == NULL) {
            perror("malloc");
            closedir(dirp);
            return -1;
        }
            strncpy(s[i], entry->d_name, MAX_NAME_LENGTH);
            s[i][MAX_NAME_LENGTH - 1] = '\0';      
            ++i;
    }
    return i;
}

int itisMusic(const char *a,char *s[])
{
    int i = 0;
    char *buf[1024]={NULL};
    int n =0;
    int cnt = 0;
    n=findMusic(a,buf);
    for(int j =0 ;j < n;++j)
    {
        if(isMUsic(buf[j]))
        {
            s[cnt] = (char*)malloc(MAX_NAME_LENGTH);
            strcpy(s[cnt], buf[j]);
         //   printf("77-buf[%d] = %s s[%d] = %s\n",j,buf[j],cnt,s[cnt]);
            //s[i][MAX_NAME_LENGTH - 1] = '\0';      

            cnt++;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        free(buf[i]); 
    }
    return cnt;

}




/*
int  main(void)
{
    char *buf[1024]={NULL};
    int n =0;
    n=itisMusic("/home/linux/王鑫/20240817/media",buf);
    for(int i = 0;i < n;++i)
    {
           printf("%s\n",buf[i]);
     }

    return 0;
}
*/


/* for (int i = 0; i < n; ++i)
    {
        printf("%s\n", buf[i]);
        free(buf[i]); // Free allocated memory
    }
*/
