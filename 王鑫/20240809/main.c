#include<stdio.h>
#include<string.h>
#include"cp_cat_cd.h"
#include"ls_ll.h"
#include"ln-s_ln.h"
#include"rm_touch_mv.h"

int main(void)
{
    _cd(".");
    putchar('$');
    putchar(' ');
    while(1)
    {
        char inputs[256] ={0};
        char *p = fgets(inputs,sizeof(inputs),stdin);
        char *s0;
        char *s1;
        char *s2;
        int i = 0;
        int counter = 0;
  	    size_t len = strlen(inputs);
        //if(NULL ==p)
        if(inputs[0]=='\n')
        {
            _cd(".");
            putchar('$');
            putchar(' ');
            continue;
        }
        inputs[strlen(inputs) - 1] ='\0';
        if (len > 0 && inputs[len - 1] == '\n') 
	    {
            inputs[len - 1] = '\0';
        }
        while('\0' !=inputs[i])
        {
            ++i;
            if(' ' ==inputs[i])
            {
                ++counter;
            }
        }
        if(inputs[0] != '\0')
        {
          //  printf("\n");
        
            if(0 == counter)
            {
		        char *rest = inputs;
                s0 = strtok(rest," ");
                if(strcmp(inputs,"ls") == 0)
                {
                    _ls(".");
                }
                else if(strcmp(inputs,"ll") == 0)
                {
                    _ll(".");
                }
                else if(strcmp(inputs,"cd") == 0)
                {
                    _cd("/home/linux");
                    putchar('$');
                    putchar(' ');
                }
                else if(strcmp(inputs,"quit") == 0)
                {
                    return -1;
                }
                else
                {
                    printf("命令错误\n");
                }
                if(strcmp(s0,"cd") != 0)
                {
                    _cd(".");
                    putchar('$');
                    putchar(' ');
                }
            }
            if(1 ==counter)
            {
		        char *rest = inputs;
                s0 = strtok(rest," ");
                s1 = strtok(NULL," ");
                if(strcmp(s0,"cat") ==0)
                {
                    _cat(s1);
                }
                else if(strcmp(s0,"cd")== 0)
                {
                    _cd(s1);
                    putchar('$');
                    putchar(' ');
                }
                else if(strcmp(s0,"ls")== 0)
                {
                    _ls(s1);
                }
                else if(strcmp(s0,"ll")== 0)
                {
                    _ll(s1);
                }
                else if(strcmp(s0,"rm")== 0)
                {
                    _rm(s1);
                }
                else if(strcmp(s0,"touch")== 0)
                {
                    _touch(s1);
                }
                else
                {
                    printf("命令错误\n");
                }
                if(strcmp(s0,"cd") != 0)
                {
                    _cd(".");
                    putchar('$');
                    putchar(' ');
                }
            }
            if(2 ==counter)
            {
        		char *rest = inputs;
                s0 = strtok(rest," ");
                s1 = strtok(NULL," ");
                s2 = strtok(NULL," ");
                if(strcmp(s0,"cp") ==0)
                {
                    _cp(s1,s2);
                }
                else if(strcmp(s0,"ln-s") == 0)
                {
                    _ln_s(s1,s2);
                }
                else if(strcmp(s0,"ln") ==0)
                {
                    _ln(s1,s2);
                }
                else if(strcmp(s0,"mv") ==0)
                {
                    _mv(s1,s2);
                }
                else
                {
                    printf("命令错误\n");
                }
                if(strcmp(s0,"cd") != 0)
                {
                    _cd(".");
                    putchar('$');
                    putchar(' ');
                }
        
            }
        }
    }
    return 0;
}
