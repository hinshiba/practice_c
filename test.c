#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BUF_SIZE = 100;

[[noreturn]] void msgexit(const char msg[]) {
    printf("%s", msg);
    exit(1);
}

int split(char* dst[], const char* src, const char* delim) {
    int n = 0;
    const char* s = src;
    char* c = strpbrk(s, delim);
    while (c) {
        strncpy(dst[n], s, c - s);
        dst[n++][c - s] = '\0';
        s = c + 1;
        c = strpbrk(s, delim);
    }
    strcpy(dst[n], s);
    dst[n++][strlen(s)] = '\0';

    // 実際の分割後の文字列数を返す
    return n;
}

int main(void) { __typeof__(int) a; }