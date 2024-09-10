#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

void aguous(char ch)
{
    char ch1,ch2;
    if(ch >= 'b' && ch <= 'y'  || ch >= 'B' && ch <= 'Y')
    {
        ch1 = ch -1;
        ch2 = ch +1;
    }
    else if(ch == 'A' || ch == 'a')
    {
        ch1 = ch + 25;
        ch2 = ch + 1;
    }
    else if(ch == 'z' || ch == 'Z')
    {
        ch1 = ch - 1;
        ch2 = ch -25;
    }
    else
    {
        puts("error!");
        assert(0);
    }
    printf("%c %c %c \n",ch1,ch,ch2);
}

int main(void)
{
    char s;
    s = getchar();
    aguous(s);
    return 0;
}



int front(int x)
{   
    if(1 == x)
    {
        return 0;    
    }
    else if(2 == x)
    {
        return 1;
    }
    else if(x % 2 == 1)
    {
        return abs(front(x - 1) + front(x - 2));
    }
    else
    {
        return abs(front(x - 1) - front(x - 2));
    }
}


void reverseString(char s[])
{
    int len = strlen(s);
    for(int i = 0;i < len  / 2;++i)
    {
        char t = s[i];
        s[i] = s[len  -i -1];
        s[len -i -1] = t;
    }

}

void bin(int n,char s[])
{
    int i = 0;
    while(n == 0)
    {
        s[i] = n % 2+ '0';           //加'0'转换为字符
        n /= 2;
        ++i;
    }
    s[i] = '\0';
    reverseString(s);
}
