#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比较函数适配 qsort
int mycmp(const void* a, const void* b)
{
    return strcmp(*(const char**)a, *(const char**)b);
}

int main()
{
    char *s[10] = {NULL}; // 存储指针的数组
    char buf[64] = {0}; // 存储输入字符串的缓冲区
    
    // 读取输入
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        perror("fgets failed");
        return 1;
    }
    
    // 去掉换行符
    buf[strcspn(buf, "\n")] = '\0';
    
    // 分割字符串
    int i = 0;
    s[i] = strtok(buf, " ");
    while (s[i] != NULL && i < 9) // 避免超出数组边界
    {
        ++i;
        s[i] = strtok(NULL, " ");
    }
    
    int n = i; // 实际的元素个数
    
    // 排序
    qsort(s, n, sizeof(char*), mycmp);
    
    // 打印结果
    for (int j = 0; j < n; ++j)
    {
        printf("%s\n", s[j]);
    }
    
    return 0;
}

