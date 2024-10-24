#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

[[noreturn]] void msgexit(const char msg[]) {
    printf("%s", msg);
    exit(1);
}

// #define listdef(T, N)  \
//     typedef struct N { \
//         T* elem;       \
//         int num;       \
//     } N;

// #define map(func, list) for

// 必要なメソッド
/*
init
at
slice
len

map
filter
fold
sort
apply
*/

typedef struct {
    const void* elem;
    const int len;
    const size_t elem_size;  // それぞれの要素の大きさ(byte)

} flist_t;

// flist_t flist_init(const void* elem, const int len, const size_t elem_size) {
//     flist_t list = {elem, len, elem_size};
//     return list;
// }

int flist_len(const flist_t* l) { return l->len; }

void* flist_at(const flist_t* l, const int n) {
    if (n < 0 || flist_len(l) <= n) {
        fprintf(stderr, "ERROR flist_at: len: %d, but accessed: %d\n", l->len,
                n);
        msgexit("flist error");
    }
    // l->elem
    // を1byteのcharのポインタにキャストして、elem_size*nを加算する
    return ((char*)l->elem) + n * l->elem_size;
}

void flist_log_int(const flist_t* l) {
    printf("flist: \n[");
    for (size_t i = 0; i < flist_len(l); i++) {
        printf("%d, ", *(int*)flist_at(l, i));
    }
    printf("]\n");
}

flist_t flist_map(void* (*func)(void* elem), flist_t* l, size_t res_elemsize) {
    // size_t elm_size = sizeof(*func(flist_at(l, 0)));
    size_t elm_size = res_elemsize;
    char* buf = malloc(l->len * elm_size);
    for (int i = 0; i < flist_len(l); ++i) {
        void* p = func(flist_at(l, i));
        memcpy(buf + i * elm_size, p, elm_size);
        free(p);  // funcが動的に確保したメモリを解放
    }
    flist_t res = {
        buf,
        l->len,
        elm_size,
    };
    return res;
}

void* multi2(void* elem) {
    int* result = malloc(sizeof(int));
    if (!result) {
        msgexit("Memory allocation failed");
    }
    *result = *((int*)elem) * 2;
    return result;
}

int main(void) {
    int a[] = {1, 2, 3};
    flist_t list = {a, 3, sizeof(int)};
    flist_log_int(&list);
    flist_t list2 = flist_map(multi2, &list, sizeof(int));
    flist_log_int(&list);
    flist_log_int(&list2);
}