#include "bigint.h"

int ascii_to_int(char ascii){
    int cor;
    cor = ascii - ASCII_NUM_0;
    return cor;
};

BigInt* bigint_input(char bigint_string[]){
    BigInt* bigint_temp = (BigInt*)malloc(sizeof(BigInt));
    char* p = bigint_string;
    int bigint_len = 0;
    int begin_flag = 1;
    while(*p != '\0'){
        if (*p == ASCII_NUM_0 && begin_flag){
            p++;
            continue;
        }
        else{
            begin_flag = 0;
            bigint_temp->number[bigint_len] = ascii_to_int(*p);
            p++;
            bigint_len++;
        }
    }

    bigint_temp->len = bigint_len;
    return bigint_temp;
};

void bigint_show(BigInt* bigint){
    unsigned long long int i;
    for (i = 0; i < bigint->len; i++){
        printf("%d", bigint->number[i]);
    }
    printf("\n");
};

int bigint_compare(BigInt* bigint_a, BigInt* bigint_b){
    // if a > b return 1 (true)
    int ans;
    int compare_flag = 1;
    int compare_digi = 0;
    if (bigint_a->len > bigint_b->len){
        ans = 1;
    } else if (bigint_a->len < bigint_b->len){
        ans = 0;
    } else {
        while (compare_flag){
            if (bigint_a->number[compare_digi] > bigint_b->number[compare_digi]) {
                compare_flag = 0;
                ans = 1;
            } else if (bigint_a->number[compare_digi] < bigint_b->number[compare_digi]){
                compare_flag = 0;
                ans = 0;
            } else {
                compare_digi++;
            }
        }
    }
    return ans;
}

BigInt* bigint_subtract(BigInt* bigint_a, BigInt* bigint_b){
    // assume a > b return a - b
    unsigned long long int gap;
    BigInt* output = (BigInt*)malloc(sizeof(BigInt));
    oneDec* string_digi = (oneDec*)malloc(sizeof(oneDec) * (MAX_DIGI_LEN));
    gap = abs(bigint_a->len - bigint_b->len);

    unsigned long long i;
    for (i=0;i<gap;i++){
        string_digi[i] = bigint_a->number[i];
    }
    for (i=gap;i<bigint_a->len;i++){
        string_digi[i] = bigint_a->number[i] - bigint_b->number[i-gap];
    }
    for (i=bigint_a->len - 1; i>0;i--){
        if (string_digi[i] < 0) {
            string_digi[i] += 10;
            string_digi[i-1] -= 1;
        }
    }
    int zero_flag = 1, zero_len = 0;
    for (i=0;i<bigint_a->len;i++){
        if (string_digi[i] == 0 && zero_flag){
            zero_len ++;
        } else {
            zero_flag = 0;
        }
    }
    if (zero_len == bigint_a->len){
        output->len = 1;
        output->number[0] = 0;
        return output;
    }

    for (i=zero_len;i<bigint_a->len;i++){
        output->number[i-zero_len] = string_digi[i];
    }
    output->len = bigint_a->len - zero_len;
    free(string_digi);
    return output;
}

BigInt* bigint_multiply(BigInt* bigint_a, BigInt* bigint_b){
    unsigned long long int maxlen, minlen, outputlen;
    BigInt *L, *S, *output;
    long long int i, j;
    
    if (bigint_compare(bigint_a, bigint_b)){
        L = bigint_a;
        S = bigint_b;
        maxlen = bigint_a->len;
        minlen = bigint_b->len;
    } else {
        L = bigint_b;
        S = bigint_a;
        maxlen = bigint_b->len;
        minlen = bigint_a->len;
    }
    

    outputlen = minlen + maxlen;
    output = (BigInt*)malloc(sizeof(BigInt));
    int string_digi[outputlen];
    for (i=0;i<outputlen;i++){
        string_digi[i] = 0;
    }
    
    for (i=minlen-1; i >=0; i--){
        for (j=maxlen-1; j>=0;j--){
            string_digi[i+j+1] += L->number[j] * S->number[i];
        }
    }

    for (j=outputlen - 1; j >= 1; j--){
        string_digi[j-1] += string_digi[j] / 10;
        string_digi[j] = string_digi[j]%10;
    }

    int start_pos = 0;
    if (string_digi[0] == 0){
        outputlen--;
        start_pos++;
    }

	
    for (i=0;i<outputlen;i++){
        output->number[i] = string_digi[start_pos+i];
    }
    output->len = outputlen;
    return output;
}

BigInt* bigint_divide_two(BigInt* bigint_a) {
    unsigned long long int outputlen;
    BigInt *output;
    long long int i, j, added;
    int temp = 0;

    outputlen = bigint_a->len;
    output = (BigInt*)malloc(sizeof(BigInt));
    int string_digi[outputlen];

    for (i=0;i<outputlen;i++){
        added = bigint_a->number[i] + temp * 10;
        string_digi[i] = added / 2;
        temp = added % 2;
    }

    int start_pos = 0;
    if (string_digi[0] == 0){
        outputlen--;
        start_pos++;
    }
    if (outputlen == 0){
        output->len = 1;
        output->number[0] = 0;
        return output;
    }

    for (i=0;i<outputlen;i++){
        output->number[i] = string_digi[start_pos+i];
    }
    output->len = outputlen;
    return output;
}

int bigint_is_zero(BigInt* bigint_a){
    int ans = 0;
    if (bigint_a->len == 1 && bigint_a->number[0] == 0){
        ans = 1;
    }
    return ans;
}

int bigint_is_even(BigInt* bigint_a){
    int ans = 0;
    unsigned long long int len = bigint_a->len;
    if (bigint_a->number[len - 1] % 2 == 0){
        ans = 1;
    }
    return ans;
}

BigInt* bigint_gcd(BigInt* bigint_a, BigInt* bigint_b){
    BigInt *bigint_L, *bigint_S, *ans, *two, *temp, *output;
    ans = (BigInt*)malloc(sizeof(BigInt));
    ans->len = 1;
    ans->number[0] = 1;
    two = (BigInt*)malloc(sizeof(BigInt));
    two->len = 1;
    two->number[0] = 2;

    if (bigint_compare(bigint_a, bigint_b)){
        bigint_L = bigint_a;
        bigint_S = bigint_b;
    } else {
        bigint_L = bigint_b;
        bigint_S = bigint_a;
    }

    while (!bigint_is_zero(bigint_S) && !bigint_is_zero(bigint_L)){

        if (bigint_is_even(bigint_S) && bigint_is_even(bigint_L)) {
            ans = bigint_multiply(ans, two);
            bigint_S = bigint_divide_two(bigint_S);
            bigint_L = bigint_divide_two(bigint_L);
        } else if (bigint_is_even(bigint_S)) {
            bigint_S = bigint_divide_two(bigint_S);
        } else if (bigint_is_even(bigint_L)) {
            bigint_L = bigint_divide_two(bigint_L);
        }

        if (bigint_compare(bigint_S, bigint_L)){
            temp = bigint_L;
            bigint_L = bigint_S;
            bigint_S = temp;
        } 
        bigint_L = bigint_subtract(bigint_L, bigint_S);
    }

    output = bigint_multiply(bigint_S, ans);
    return output;
}