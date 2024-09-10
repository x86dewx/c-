#include <stdio.h>
#include <string.h>

int main(void) {
    char s[] = "I LOVE CHINA";
    int length = strlen(s);
    char *p = s + length - 1, *q = p;

    // 找到最后一个单词的开头
    while (p > s && *p != ' ') {
        --p;
    }
    if (p != s) {
        ++p;
    }

    // 打印最后一个单词
    for (char *r = p; r <= q; ++r) {
        putchar(*r);
    }
    putchar(' ');

    // 反向查找第二个单词
    q = p - 2;
    p = q;
    while (p >= s && *p != ' ') {
        --p;
    }
    ++p;

    // 打印第二个单词
    for (char *r = p; r <= q; ++r) {
        putchar(*r);
    }
    putchar(' ');

    // 反向查找第一个单词
    q = p - 2;
    p = s;
    
    // 打印第一个单词
    for (char *r = p; r <= q; ++r) {
        putchar(*r);
    }
    putchar('\n');

    return 0;
}

