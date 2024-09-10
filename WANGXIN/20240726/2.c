#include<stdio.h>
#include<string.h>

void findUpAndDown(char s[][100],int rows)

{
    int i;
    for(i = 0;i < rows;++i)
    {
        for(int j =i + 1;j < rows;++j)
        {
            if(strcmp(s[i],s[j]) > 0)
            {
                char t[100];
                strcpy(t,s[i]);
                strcpy(s[i],s[j]);
                strcpy(s[j],t);
            }
        }
    }
}

int finewhere(char s[][100],int rows,char a[])
{
    int begin,end,mid,i;
    i = 0;
    begin = 0;
    end =rows;
    while(begin <= end )
    {
        mid = (begin + end) / 2;
        if(strcmp(s[mid], a) > 0)
        {
            end = mid -1;
        }
        else if(strcmp(s[mid],a) < 0)
        {
            begin = mid + 1;
        }
        else
        {
            break;
        }
    }
    if(begin <= end)
    {
        return mid;
    }
    return -1;
}

int main(void)
{
    char s[][100] ={"china","hello","world"};
    char a[]="hello";
    int rows =sizeof(s) /sizeof(s[0]);
    findUpAndDown(s,rows);
    int ret = finewhere(s,rows,a);
    if(ret < 0)
    {
        printf("Not find");
    }
    else
    {
        printf("find\n%d\n",ret);
    }

}
