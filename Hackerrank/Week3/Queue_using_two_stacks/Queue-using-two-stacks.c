#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct Stack {
    int* data;
    int top;
    int capacity;
}Stack;

Stack* createStack(int capacity){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if(!stack){
        return NULL;
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (int*)malloc(stack->capacity * sizeof(int));
    if(!stack->data){
        return NULL;
    }
    return stack;
}

int isEmpty(Stack* stack){
    return stack->top == -1;
}

int isFull(Stack* stack){
    return stack->top == stack->capacity - 1;
}

void push(Stack* stack, int item){
    if(isFull(stack)){ 
        printf("Stack is full, cannot push. \n");
        return;
    }
    stack->data[++stack->top] = item;
}

int pop(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is empty, cannot pop.\n");
        return -1;
    } 
    return stack->data[stack->top--];
}

int peek(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is empty, no front element.\n");
         return -1;
    }
    return stack->data[stack->top];
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    
    int num_queries;
    scanf("%d", &num_queries);
    
    Stack* enqueue_stack = createStack(100000);
    Stack* dequeue_stack = createStack(100000);
    
    for(int i=0;i<num_queries;i++){
        int query_type;
        scanf("%d", &query_type);
        
        if(query_type == 1){
            int data;
            scanf("%d", &data);
            push(enqueue_stack, data);
        }else{
            if(isEmpty(dequeue_stack)){
                while(!isEmpty(enqueue_stack)){
                    push(dequeue_stack, pop(enqueue_stack));
                }
            }
            
            if(query_type == 2){
                if(!isEmpty(dequeue_stack)){
                    pop(dequeue_stack);
                }
            }else if(query_type == 3){
                if(!isEmpty(dequeue_stack)){
                    printf("%d\n", peek(dequeue_stack));
                }
            }
        }
    }
    
    free(enqueue_stack->data);
    free(enqueue_stack);
    free(dequeue_stack->data);
    free(dequeue_stack);
    
    return 0;
}
