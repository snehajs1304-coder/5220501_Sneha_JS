#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'waiter' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY number
 *  2. INTEGER q
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */
 
int* waiter(int number_count, int* number, int q, int* result_count) {
    
    const int MAX_PRIME_LIMIT = 10000;
    bool is_prime[MAX_PRIME_LIMIT + 1];
    for(int i=0;i<=MAX_PRIME_LIMIT;i++){
        is_prime[i] = true;
    }
    is_prime[0] = false;
    is_prime[1] = false;
    for(int p=2;p*p <= MAX_PRIME_LIMIT; ++p){
    if(is_prime[p]){
    for(int i=p*p;i<=MAX_PRIME_LIMIT;i += p){
    is_prime[i] = false;    
    }
    }
    }
    
    int primes[q];
    int prime_count = 0;
    for(int i=2;i<= MAX_PRIME_LIMIT && prime_count<q; ++i){
        if(is_prime[i]){
            primes[prime_count++] = i;
        }
    }
    
    int** stacks_A = (int**)malloc((q+1)*sizeof(int*));
    int* tops_A = (int*)malloc((q+1) * sizeof(int));
    for(int i=0;i<=q;++i){
        stacks_A[i] = (int*)malloc(number_count * sizeof(int));
        tops_A[i] = -1;
        }
    
    int* stack_B = (int*)malloc(number_count*sizeof(int));
    int top_B = -1;
    
    for(int i= 0;i<number_count; i++){
        stacks_A[0][++tops_A[0]] = number[i];
    } 
    
    int* result = (int*)malloc(number_count * sizeof(int));
    int result_idx = 0;
    
    for(int i=0;i<q;++i){
        int current_prime = primes[i];
        top_B = -1;
        
        while(tops_A[i] != -1){
            int plate_number = stacks_A[i][tops_A[i]--];
            if(plate_number % current_prime == 0){
                stack_B[++top_B] = plate_number;
            }else{
                stacks_A[i+1][++tops_A[i+1]] = plate_number;
            }
        }
        
        while(top_B != -1){
            result[result_idx++] = stack_B[top_B--];
        } 
    }
    
    while(tops_A[q] != -1){
        result[result_idx++] = stacks_A[q][tops_A[q]--];
    }
    
    *result_count = result_idx;
    
    for(int i=0;i<=q;i++){
        free(stacks_A[i]);
    }
    
    free(stacks_A);
    free(tops_A);
    free(stack_B);
    
    return result;
 }
 
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int q = parse_int(*(first_multiple_input + 1));

    char** number_temp = split_string(rtrim(readline()));

    int* number = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int number_item = parse_int(*(number_temp + i));

        *(number + i) = number_item;
    }

    int result_count;
    int* result = waiter(n, number, q, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
