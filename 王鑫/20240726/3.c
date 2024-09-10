#include <stdio.h>
#include <string.h>

void strcopy(char dest[], const char src[]) {
    int i = 0;
    while (src[i]) {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0'; // 添加空终止符
}

void reverseStrings(char s[][100], int rows) {
    for (int i = 0; i < rows / 2; ++i) {
        char t[100];
        strcopy(t, s[i]);
        strcopy(s[i], s[rows - 1 - i]);
        strcopy(s[rows - 1 - i], t);
    }
}

void printfArray2D(char s[][100], int rows) {
    for (int i = 0; i < rows; ++i) {
        puts(s[i]);
    }
}

void sortArray2D(char s[][100], int rows) {
    for (int i = 0; i < rows - 1; ++i) {
        for (int j = i + 1; j < rows; ++j) {
            if (strcmp(s[i], s[j]) > 0) {
                char t[100];
                strcopy(t, s[i]);
                strcopy(s[i], s[j]);
                strcopy(s[j], t);
            }
        }
    }
}

int main(void) {
    char a[3][100] = {"hello", "world", "china"};
    int rows = sizeof(a) / sizeof(a[0]);
    sortArray2D(a, rows);
    printfArray2D(a, rows);
    return 0;
}

