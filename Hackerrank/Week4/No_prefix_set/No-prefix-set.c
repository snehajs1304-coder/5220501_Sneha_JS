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

int parse_int(char*);

/*
 * Complete the 'noPrefix' function below.
 *
 * The function accepts STRING_ARRAY words as parameter.
 */
 typedef struct TrieNode {
    struct TrieNode *children[26]; // 'a' through 'j' only, but we use 26 for simplicity and potential future changes
    bool isEndOfWord;
    bool hasPrefix; // To indicate if this node is a prefix of another word
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    node->hasPrefix = false;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void noPrefix(int words_count, char** words) {
     TrieNode* root = createNode();
    bool badSetFound = false;
    char* badWord = NULL;

    for (int i = 0; i < words_count; i++) {
        char* currentWord = words[i];
        TrieNode* current = root;
        bool isCurrentWordPrefix = true; // Assume current word is a prefix until proven otherwise
        
        for (int j = 0; currentWord[j] != '\0'; j++) {
            int index = currentWord[j] - 'a';

            if (current->isEndOfWord) { // If we encounter an endOfWord flag before reaching the end of currentWord, it means a shorter word is a prefix of currentWord
                badSetFound = true;
                badWord = currentWord;
                break;
            }
            
            if (current->children[index] == NULL) {
                current->children[index] = createNode();
                isCurrentWordPrefix = false; // Current word extends the trie, so it cannot be a prefix of an already existing word
            }
            current = current->children[index];
        }

        if (badSetFound) { // Exit if bad set already found
            break;
        }

        if (current->hasPrefix || (current->isEndOfWord && isCurrentWordPrefix)) { // current->isEndOfWord for identical strings (they are prefixes of each other) [page 1]
            badSetFound = true;
            badWord = currentWord;
            break;
        }
        
        current->isEndOfWord = true; // Mark the end of the current word
        
        // Mark all nodes on the path of the newly inserted word as having a prefix
        TrieNode* temp = root;
        for (int j = 0; currentWord[j] != '\0'; j++) {
            int index = currentWord[j] - 'a';
            temp = temp->children[index];
            if (temp->isEndOfWord && temp != current) { // If a longer word exists that has this shorter word as a prefix
                badSetFound = true;
                badWord = currentWord; // The newly added word is a prefix of existing word
                break;
            }
            if (j < strlen(currentWord) - 1) { // Only mark hasPrefix for intermediate nodes
                 temp->hasPrefix = true;
            }
        }
        if (badSetFound) {
            break;
        }
    }

    if (badSetFound) {
        printf("BAD SET\n");
        printf("%s\n", badWord);
    } else {
        printf("GOOD SET\n");
    }

    // Free the allocated Trie memory (optional for competitive programming, good practice otherwise)
    // You'd need a recursive helper function for this

}

int main()
{
    int n = parse_int(ltrim(rtrim(readline())));

    char** words = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* words_item = readline();

        *(words + i) = words_item;
    }

    noPrefix(n, words);

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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
