#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define getfmt(x) \
    _Generic(x, int: "%d", double: "%f", char: "%c", char*: "%s", int*: "%p")

#define dbglog(i, fmt) printf("%s is set: " fmt "\n", #i, i)
#define dbglog2(i)                 \
    do {                           \
        printf("%s is set: ", #i); \
        printf(getfmt(i), i);      \
        printf("\n");              \
    } while (0)

char* hoge(void) { return "aa"; }

void dbglog3() {}
int main(void) {
    // printf(
    //     "%d"
    //     "\n",
    //     a);
    // printf(_Generic(a, int: "%d"), a);
    // printf(hoge() "\n", a);
    // printf(_Generic(a, int: "%d") "\n", a);
    int a = 5;
    double b = 2.5;
    char c = 'c';
    char s[] = "str";
    int* p = &a;
    dbglog2(a);
    dbglog2(b);
    dbglog2(c);
    dbglog2(s);
    dbglog2(p);
}