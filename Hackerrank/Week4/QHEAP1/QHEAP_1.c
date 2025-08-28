#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAXQ 100000

void swap(int *a, int *b){
    int t = *a; *a = *b; *b = t;
}

void heapify_up(int heap[], int idx){
    while(idx > 0){
        int parent = (idx - 1) / 2;
        if(heap[parent] <= heap[idx]) break;
        swap(&heap[parent], &heap[idx]);
        idx = parent;
    }
}

void heapify_down(int heap[], int size, int idx){
    while(1){
        int left = 2 * idx + 1, right = 2 * idx + 2, smallest = idx;
        if(left < size && heap[left] < heap[smallest])
            smallest = left;
        if(right < size && heap[right] < heap[smallest])
            smallest = right;
        if(smallest == idx) break;
        swap(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

void heap_push( int heap[], int *size, int val){
    heap[*size] = val;
    heapify_up(heap, *size);
    (*size)++;
}

int heap_top(int heap[]){
    return heap[0];
}

void heap_pop(int heap[], int *size){
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify_down(heap, *size, 0);
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int Q;
    scanf("%d", &Q);
    
    int heap[MAXQ];
    int size = 0;
    int deleteHeap[MAXQ];
    int dsize = 0;
    
    while(Q--){
        int type, val;
        scanf("%d", &type);
        
        if(type == 1){
            scanf("%d", &val);
            heap_push(heap, &size, val);
        }
        else if(type == 2){
            scanf("%d", &val);
            heap_push(deleteHeap, &dsize, val);
        }
        else{
            while(size > 0 && dsize > 0 && heap_top(heap) == heap_top(deleteHeap)){
                heap_pop(heap, &size);
                heap_pop(deleteHeap, &dsize);
            }
            printf("%d\n", heap_top(heap));
        }
    }
        
    return 0;
}
