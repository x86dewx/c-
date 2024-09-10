#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd1[2]; // 父子进程间通信管道
    int fd2[2]; // 子父进程间通信管道
    
    // 创建第一个管道
    if (pipe(fd1) < 0) {
        perror("pipe1 fail");
        return -1;
    }
    
    // 创建第二个管道
    if (pipe(fd2) < 0) {
        perror("pipe2 fail");
        return -1;
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork fail");
        return -1;
    }
    
    if (pid > 0) { // 父进程
        close(fd1[0]); // 关闭读端
        close(fd2[1]); // 关闭写端
        
        while (1) {
            char buf[1024] = {0};
            printf("父进程: 请输入数据：");
            fflush(stdout); // 确保提示信息立即输出
            if (fgets(buf, sizeof(buf), stdin) == NULL) {
                perror("fgets fail");
                break;
            }
            // 移除换行符
            buf[strcspn(buf, "\n")] = '\0';
            
            char buf2[] = "hello child";
            char buf3[1024] = {0};
            
            // 从管道中读取子进程的消息
            ssize_t n = read(fd2[0], buf3, sizeof(buf3));
            if (n > 0) {
                printf("父进程收到: %s\n", buf3);
            }
            
            // 写数据到管道
            if (write(fd1[1], buf, strlen(buf) + 1) < 0) {
                perror("write fail");
                break;
            }
            
            if (strcmp(buf, "exit") == 0) {
                // 向子进程发送退出信号
                write(fd1[1], buf2, strlen(buf2) + 1);
                printf("父进程发送: %s\n", buf2);
                break;
            }
        }
        
        // 等待子进程退出
        wait(NULL);
    } else { // 子进程
        close(fd1[1]); // 关闭写端
        close(fd2[0]); // 关闭读端
        
        while (1) {
            char buf[1024] = {0};
            ssize_t n = read(fd1[0], buf, sizeof(buf));
            if (n > 0) {
                printf("子进程收到: %s\n", buf);
                char buf2[] = "hello father";
                
                if (strcmp(buf, "exit") == 0) {
                    exit(0);
                } else {
                    if (write(fd2[1], buf2, strlen(buf2) + 1) < 0) {
                        perror("write fail");
                        exit(-1);
                    }
                    printf("子进程发送: %s\n", buf2);
                }
            }
        }
    }
    
    return 0;
}

