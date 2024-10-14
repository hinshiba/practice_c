#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dbglog(i, fmt) printf("%s is set: " fmt "\n", #i, i)

const int BUF_SIZE = 100;
const int INPUT_BASE = 10;

void msgexit(const char msg[]) {
    printf("%s", msg);
    exit(1);
}

// fgetsヘルパ

void input(const char dialog[], char buf[], const int buf_size) {
    printf("%s", dialog);
    if (fgets(buf, buf_size, stdin) == NULL || buf[0] == '\n') {
        msgexit("not input");
    }
    size_t len = strlen(buf);
    if (buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    }
}

// パーサー

int parse_int(char* str) {
    char* e;
    long l = strtol(str, &e, INPUT_BASE);
    if (*e != '\0') msgexit("parse error");
    if (INT_MAX < l || l < INT_MIN) msgexit("not int yes long");
    return (int)l;
}

double parse_double(char* str) {
    char* e;
    double d = strtod(str, &e);
    if (*e != '\0') msgexit("parse error");
    return d;
}

// 単数入力

int input_int(char dialog[]) {
    char buf[BUF_SIZE];
    input(dialog, buf, BUF_SIZE);
    return parse_int(buf);
}

double input_double(char dialog[]) {
    char buf[BUF_SIZE];
    input(dialog, buf, BUF_SIZE);
    return parse_double(buf);
}

// 複数入力関係

void inputs(const char dialog[], const char fmt[], ...) {
    if (fmt == NULL) msgexit("fmt is null");
    if (strlen(fmt) < 2) msgexit("maybe not %%x");
    char buf[BUF_SIZE];
    input(dialog, buf, BUF_SIZE);
    // 入力を分割
    const char SPLIT[] = " ,";
    char* ctx;
    char* tkn = strtok_s(buf, SPLIT, &ctx);

    va_list arg;
    va_start(arg, fmt);

    size_t i = 0;

    while (fmt[i] != '\0' && fmt[i + 1] != '\0') {
        if (tkn == NULL) {
            msgexit("input too short");
        }
        if (fmt[i] == '%') {
            if (fmt[i + 1] == 's') {
                char* ptr = va_arg(arg, char*);
                strncpy_s(ptr, BUF_SIZE, tkn, _TRUNCATE);
            } else if (fmt[i + 1] == 'c') {
                if (strlen(tkn) != 1) msgexit("expected single character");
                char* ptr = va_arg(arg, char*);
                *ptr = tkn[0];
            } else if (fmt[i + 1] == 'd') {
                int* ptr = va_arg(arg, int*);
                *ptr = parse_int(tkn);
            } else if (fmt[i + 1] == 'f') {
                double* ptr = va_arg(arg, double*);
                *ptr = parse_double(tkn);
            } else {
                msgexit("not impl unk %%");
            }
        } else {
            msgexit("not impl unk ");
        }
        tkn = strtok_s(NULL, SPLIT, &ctx);
        i += 2;
    }
    va_end(arg);
}