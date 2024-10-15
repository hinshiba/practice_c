#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BUF_SIZE = 100;

[[noreturn]] void msgexit(const char msg[]) {
    printf("%s", msg);
    exit(1);
}

void inputln(const char dialog[], char buf[], const int buf_size) {
    printf("%s", dialog);
    if (fgets(buf, buf_size, stdin) == NULL || buf[0] == '\n') {
        msgexit("not input");
    }
    size_t len = strlen(buf);
    if (buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    }
}

#define getfmt(x) \
    _Generic(x, int: "%d", double: "%f", char: "%c", char*: "%s", int*: "%p")

void inputs(const char dialog[], ...) {
    char buf[BUF_SIZE];
    inputln(dialog, buf, BUF_SIZE);
    // 入力を分割
    const char SPLIT[] = " ,";
    char* ctx;
    char* tkn = strtok_s(buf, SPLIT, &ctx);

    va_list arg;
    va_start(arg, dialog);

    size_t i = 0;

    while (arg != NULL) {
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

int main(void) { __typeof__(int) a; }