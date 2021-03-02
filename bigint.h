#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define ASCII_NUM_9 57
#define ASCII_NUM_0 48
#define MAX_DIGI_LEN 500

typedef char oneDec;
typedef struct bigint {
    oneDec number[MAX_DIGI_LEN];
    unsigned long long len;
} BigInt;

int ascii_to_int(char ascii);
BigInt* bigint_input(char bigint_string[]);
void bigint_show(BigInt* bigint);

int bigint_is_zero(BigInt* bigint_a);
int bigint_compare(BigInt* bigint_a, BigInt* bigint_b);
BigInt* bigint_subtract(BigInt* bigint_a, BigInt* bigint_b);
BigInt* bigint_multiply(BigInt* bigint_a, BigInt* bigint_b);
BigInt* bigint_divide_two(BigInt* bigint_a);
BigInt* bigint_gcd(BigInt* bigint_a, BigInt* bigint_b);