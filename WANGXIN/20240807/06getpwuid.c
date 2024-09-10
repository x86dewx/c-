#include<stdio.h>
#include<sys/types.h>
#include<pwd.h>

int main(int argc,char *argv[])
{
    uid_t uid = 1000;
    struct passwd *pw =getpwuid(uid);
    printf("name:%s gid:%d infp:%s wd:%s shell:%s\n",pw->pw_name,pw->pw_gid,pw->pw_gecos,pw->pw_dir,pw->pw_shell);

    return 0;
}
