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
 * Complete the 'minimumMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY grid
 *  2. INTEGER startX
 *  3. INTEGER startY
 *  4. INTEGER goalX
 *  5. INTEGER goalY
 */
 typedef struct{
    int x;
    int y;
    int moves;
 }State;

int minimumMoves(int grid_count, char** grid, int startX, int startY, int goalX, int goalY) {
    int n = grid_count;
    bool visited[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            visited[i][j] = false;
        }
    }
    
    State* queue = malloc(n * n * sizeof(State));
    int front = 0, rear = 0;
    
    State start_state = {startX, startY, 0};
    queue[rear++] = start_state;
    visited[startX][startY] = true;
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while(front < rear){
        State current = queue[front++];
        
        if(current.x == goalX && current.y == goalY){
            free(queue);
            return current.moves;
        }
        
        for(int i = 0; i < 4; i++){
            int newX = current.x;
            int newY = current.y;
            
            while(true){
                newX += dx[i];
                newY += dy[i];
                
                if(newX < 0 || newX >= n || newY < 0 || newY >= n){
                    break;
                }
                if(grid[newX][newY] == 'X'){
                    break;
                }
                
                if(!visited[newX][newY]){
                    visited[newX][newY] = true;
                    State next_state = {newX, newY, current.moves + 1};
                    queue[rear++] = next_state;
                }
            }
        }
    }
    free(queue);
    return -1;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** grid = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* grid_item = readline();

        *(grid + i) = grid_item;
    }

    char** first_multiple_input = split_string(rtrim(readline()));

    int startX = parse_int(*(first_multiple_input + 0));

    int startY = parse_int(*(first_multiple_input + 1));

    int goalX = parse_int(*(first_multiple_input + 2));

    int goalY = parse_int(*(first_multiple_input + 3));

    int result = minimumMoves(n, grid, startX, startY, goalX, goalY);

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
