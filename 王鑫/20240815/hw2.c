#include<head.h>

int mycmp(const void* a,const void* b)
{
    return strcmp((const char*)a,(const char*)b);
}


int main(int argc, char *argv[])
{
    char *s[10] ={NULL};
    char buf[64] ={0};
    fgets(buf,sizeof(buf),stdin);
    buf[strlen(buf) - 1] ='\0';
    *s =strtok(buf," ");
    int i = 0;
    while(*(s + i ) !=NULL)
    {
        ++i;
        *(s + i) =strtok(NULL," ");
    }
    int n = i;
    qsort(s,n,sizeof(char *),mycmp);
    for(int j = 0;j < n;++j)
    {
        printf("%s\n",s[j]);
    }
    
    return 0;
}
