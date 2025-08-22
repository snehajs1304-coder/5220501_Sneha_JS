#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define INITIAL_STRING_CAPACITY 1024
#define INITIAL_STACK_CAPACITY 1000

// Dynamic stack for storing previous string states
char **stack = NULL;
int top = -1;
int stack_capacity = 0;

// Function to resize the stack if needed
void resize_stack() {
    if (stack_capacity == 0) {
        stack_capacity = INITIAL_STACK_CAPACITY;
        stack = (char **)malloc(stack_capacity * sizeof(char *));
        if (stack == NULL) {
            perror("Failed to allocate stack memory");
            exit(EXIT_FAILURE);
        }
    } else if (top >= stack_capacity - 1) {
        stack_capacity *= 2;
        char **new_stack = (char **)realloc(stack, stack_capacity * sizeof(char *));
        if (new_stack == NULL) {
            perror("Failed to reallocate stack memory");
            // Attempt to continue with the existing stack, but this is a critical error
            // It might be safer to exit here depending on requirements
            exit(EXIT_FAILURE); 
        }
        stack = new_stack;
    }
}

void push(char *s) {
    resize_stack();
    stack[++top] = strdup(s); // Duplicate the string and store the pointer
    if (stack[top] == NULL) {
        perror("Failed to duplicate string for stack");
        exit(EXIT_FAILURE);
    }
}

char *pop() {
    if (top < 0) {
        return NULL; // Indicates an empty stack, should be handled by caller
    }
    return stack[top--];
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
  int Q;
    scanf("%d", &Q);

    char *S = (char *)malloc(INITIAL_STRING_CAPACITY * sizeof(char));
    if (S == NULL) {
        perror("Failed to allocate initial string memory");
        return EXIT_FAILURE;
    }
    S[0] = '\0'; // Initialize S as an empty string
    int s_len = 0;
    int s_capacity = INITIAL_STRING_CAPACITY;

    while (Q--) {
        int type;
        scanf("%d", &type);

        if (type == 1) { // append
            char W[100000]; // W can be up to 10^5 chars according to problem constraints
            scanf("%s", W);
            
            push(S); // Save current state of S

            int w_len = strlen(W);
            int new_len = s_len + w_len;
            if (new_len >= s_capacity) {
                // Double the capacity until it's large enough
                while (new_len >= s_capacity) {
                    s_capacity *= 2;
                }
                char *new_S = (char *)realloc(S, s_capacity * sizeof(char));
                if (new_S == NULL) {
                    perror("Failed to reallocate string memory for append");
                    exit(EXIT_FAILURE);
                }
                S = new_S;
            }
            strcat(S, W);
            s_len = new_len;

        } else if (type == 2) { // delete last k chars
            int k;
            scanf("%d", &k);

            push(S); // Save current state of S

            if (k >= s_len) { // If deleting all or more characters
                S[0] = '\0';
                s_len = 0;
            } else {
                S[s_len - k] = '\0';
                s_len -= k;
            }

        } else if (type == 3) { // print kth char
            int k;
            scanf("%d", &k);
            if (k > 0 && k <= s_len) {
                printf("%c\n", S[k - 1]);
            } else {
                // Problem constraints usually guarantee valid k, but it's good practice
                // to handle out-of-bounds access if it's not guaranteed.
                // printf("Error: Index out of bounds\n"); 
            }
        } else if (type == 4) { // undo
            char *prev = pop();
            if (prev != NULL) {
                strcpy(S, prev);
                s_len = strlen(S);
                free(prev); // Free the memory allocated by strdup
            } else {
                // Stack is empty, nothing to undo.
                // According to problem statements, this operation should be valid
                // so an empty string results.
                S[0] = '\0';
                s_len = 0;
            }
        }
    }

    // Free the final string and the stack memory
    free(S);
    while (top >= 0) { // Free any remaining strings on the stack
        free(stack[top--]);
    }
    free(stack);
    return 0;
}
