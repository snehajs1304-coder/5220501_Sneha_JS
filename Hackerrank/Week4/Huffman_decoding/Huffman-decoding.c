#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

struct node {
    int freq;
    char data;
    struct node *left, *right;
};

// ---------- Priority Queue (Min-Heap) ----------
struct MinHeap {
    int size;
    int capacity;
    struct node **array;
};

struct node* newNode(char data, int freq) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->array = (struct node**)malloc(minHeap->capacity * sizeof(struct node*));
    return minHeap;
}

void swapNode(struct node** a, struct node** b) {
    struct node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct node* extractMin(struct MinHeap* minHeap) {
    struct node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct node* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct node* buildHuffmanTree(char data[], int freq[], int size) {
    struct node *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// ---------- Huffman Decoding ----------
void decode_huff(struct node *root, char *s) {
    struct node *curr = root;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (curr->left == NULL && curr->right == NULL) {
            printf("%c", curr->data);
            curr = root;
        }
    }
}

// ---------- Generate Codes ----------
void storeCodes(struct node* root, char* code, int top, char codes[256][256]) {
    if (root->left) {
        code[top] = '0';
        storeCodes(root->left, code, top + 1, codes);
    }
    if (root->right) {
        code[top] = '1';
        storeCodes(root->right, code, top + 1, codes);
    }
    if (root->left == NULL && root->right == NULL) {
        code[top] = '\0';
        strcpy(codes[(unsigned char)root->data], code);
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
     char input[1000];
    scanf("%[^\n]", input);

    // frequency count
    int freq[256] = {0};
    int unique = 0;
    char chars[256];

    for (int i = 0; input[i] != '\0'; i++) {
        if (freq[(unsigned char)input[i]] == 0)
            chars[unique++] = input[i];
        freq[(unsigned char)input[i]]++;
    }

    int charFreq[256];
    for (int i = 0; i < unique; i++) {
        charFreq[i] = freq[(unsigned char)chars[i]];
    }

    // Build Huffman Tree
    struct node* root = buildHuffmanTree(chars, charFreq, unique);

    // Generate codes
    char codes[256][256] = {{0}};
    char arr[256];
    storeCodes(root, arr, 0, codes);

    // Encode input
    char encoded[10000] = "";
    for (int i = 0; input[i] != '\0'; i++) {
        strcat(encoded, codes[(unsigned char)input[i]]);
    }

    // Decode back
    decode_huff(root, encoded);
    printf("\n");

    return 0;
}
