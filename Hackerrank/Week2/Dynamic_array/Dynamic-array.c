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
 * Complete the 'dynamicArray' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY queries
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
int* dynamicArray(int n, int queries_rows, int queries_columns, int** queries, int* result_count) {
    
    int*** seqlist = (int***)malloc(n* sizeof(int**));
    int* seqsizes = (int*)malloc(n*sizeof(int));
    int* seqcapacities = (int*)malloc(n*sizeof(int));
    
    for(int i=0;i<n;i++)
    {
        seqlist[i] = NULL;
        seqsizes[i] = 0;
        seqcapacities[i] = 0;
    }
    int lastanswer = 0;
    
    int* results = (int*)malloc(queries_rows * sizeof(int));
    int resultindex = 0;
    
    for(int i=0;i<queries_rows;i++)
    {
        int querytype = queries[i][0];
        int x = queries[i][1];
        int y = queries[i][2];
        
        int idx = (x ^ lastanswer) % n;
        
        if(querytype == 1)
        {
            if(seqsizes[idx] == seqcapacities[idx])
            {
                seqcapacities[idx] = (seqcapacities[idx] == 0)?1:seqcapacities[idx] * 2;
                seqlist[idx] = (int**)realloc(seqlist[idx], seqcapacities[idx] * sizeof(int*));
                
                if(seqlist[idx] == NULL)
                {
                    fprintf(stderr, "realloc failed in type 1 query\n");
                    exit(EXIT_FAILURE);
                }
            }
            
            seqlist[idx][seqsizes[idx]] = (int*)malloc(sizeof(int));
            if(seqlist[idx][seqsizes[idx]] == NULL)
            {
                fprintf(stderr, "malloc failed for new element in type 1 query\n");
                exit(EXIT_FAILURE);
            }
            *(seqlist[idx][seqsizes[idx]]) = y;
            seqsizes[idx]++;
        }else{
            int elementindex = y % seqsizes[idx];
            lastanswer= *(seqlist[idx][elementindex]);
            results[resultindex++] = lastanswer;
        }
    }
    *result_count = resultindex;
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<seqsizes[i];j++)
        {
            free(seqlist[i][j]);
        }
        free(seqlist[i]);
    }
    free(seqlist);
    free(seqsizes);
    free(seqcapacities);
    
    results = (int*)realloc(results, resultindex * sizeof(int));
    if(results == NULL && resultindex > 0)
    {
        fprintf(stderr, "realloc failed for final results array\n");
        exit(EXIT_FAILURE);
    }
    return results;
}


int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int q = parse_int(*(first_multiple_input + 1));

    int** queries = malloc(q * sizeof(int*));

    for (int i = 0; i < q; i++) {
        *(queries + i) = malloc(3 * (sizeof(int)));

        char** queries_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 3; j++) {
            int queries_item = parse_int(*(queries_item_temp + j));

            *(*(queries + i) + j) = queries_item;
        }
    }

    int result_count;
    int* result = dynamicArray(n, q, 3, queries, &result_count);

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
