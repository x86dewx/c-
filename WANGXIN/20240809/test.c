#include<stdio.h>
#include"cp_cat_cd.h"
#include"ln-s_ln.h"
#include"rm_touch_mv.h"
int main(int argc, char *argv[])
{
    _rm("text2");
    _touch("text3");
    _mv("text1","text3");
    return 0;
}
