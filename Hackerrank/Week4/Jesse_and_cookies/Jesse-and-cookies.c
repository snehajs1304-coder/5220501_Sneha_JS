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
 * Complete the 'cookies' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY A
 */
 void heapify(int* heap, int n, int i){
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if(left < n && heap[left] < heap[smallest])
        smallest = left;
    if(right < n && heap[right] < heap[smallest])
        smallest = right;
        
    if(smallest != i){
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        
        heapify(heap, n, smallest);
    }
 }
 
 void buildheap(int* heap, int n){
    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(heap, n, i);
    }
 }
 
 int extractmin(int* heap, int* n){
    if(*n <=0) return INT_MAX;
    if(*n == 1){
        (*n)--;
        return heap[0];
    }
    
    int root = heap[0];
    heap[0] = heap[*n - 1];
    (*n)--;
    heapify(heap, *n, 0);
    return root;
 }
 
 void insertheap(int* heap, int* n, int key){
    (*n)++;
    int i = *n - 1;
    heap[i] = key;
    
    while(i != 0 && heap[(i - 1) / 2] > heap[i]){
        int temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
 }

int cookies(int k, int A_count, int* A) {
    int n = A_count;
    int ops = 0;
    
    buildheap(A, n);
    
    while(n > 1 && A[0] < k){
        int first = extractmin(A, &n);
        int second = extractmin(A, &n);
        
        int newsweetness = first + 2 * second;
        
        insertheap(A, &n, newsweetness);
        ops++;
    }
    if(A[0] >= k) return ops;
    else return -1;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    char** A_temp = split_string(rtrim(readline()));

    int* A = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int A_item = parse_int(*(A_temp + i));

        *(A + i) = A_item;
    }

    int result = cookies(k, n, A);

    fprintf(fptr, "%d\n", result);

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
