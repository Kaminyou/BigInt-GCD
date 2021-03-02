#include <stdio.h>
#include <assert.h>
#include "bigint.h"
int main(int argc, char *argv[]){
    assert(argc == 3);
    BigInt *bigint_a, *bigint_b, *bigint_temp;
    char input[MAX_DIGI_LEN + 1];
    bigint_a = bigint_input(argv[1]);

    bigint_b = bigint_input(argv[2]);

    bigint_temp = bigint_gcd(bigint_a, bigint_b);
    bigint_show(bigint_temp);
    return 0;
};