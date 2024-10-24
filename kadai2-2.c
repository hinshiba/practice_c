#include <stdio.h>

const int LOOP_NUM = 10;

// MSG
#define MSG_RESULT(k, k_s, a) "k=%d, k!=%d, a=%f\n", k, k_s, a

int main(void) {
    float a = 1.0;
    int factorial = 1;
    for (int k = 1; k <= LOOP_NUM; k++) {
        factorial *= k;
        a += 1.0 / factorial;
        printf(MSG_RESULT(k, factorial, a));
    }
}
