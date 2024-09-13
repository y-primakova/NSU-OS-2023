#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_STR 2048

typedef struct Node {
    char* string;
    struct Node* next;
} Node;

void freeList(Node* start) {
    Node* node;
    while (start != NULL) {
        node = start;
        start = start->next;
        free(node->string);
        free(node);
    }
}

Node* initNode(char* str, Node* start) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        perror("Memory for node isn't allocated.");
        freeList(start);
        exit(-1);
    }
    node->string = (char*)malloc(strlen(str) + 1);
    if (node->string == NULL) {
        perror("Memory for string isn't allocated.");
        free(node);
        freeList(start);
        exit(-1);
    }
    strcpy(node->string, str);
    node->next = NULL;
    return node;
}

void addNode(char* str, Node* start) {
    Node* node = start;
    while (node->next != NULL) {
        node = node->next;
    }
    node->next = initNode(str, start);
}

void printList(Node* start) {
    Node* node = start;
    printf("\n");
    while (node != NULL) {
        printf("%s",node->string);
        node = node->next;
    }
}


int main() {
    char str[SIZE_STR + 1];
    Node* start = NULL;
    int newLine = 1;
    while(1) {
        char* line = fgets(str, SIZE_STR, stdin);
        if (line == NULL) {
            if (feof(stdin)) {
                break;
            } else {
                perror("Fgets fail.");
                exit(-1);
            }
        }
        if (str[0] == '.' && newLine) {
            break;
        }
        if (str[strlen(line) - 1] != '\n') {
            newLine = 0;
        } else {
            newLine = 1;
        }
        if (start == NULL) {
            start = initNode(str, start);
        } else {
            addNode(str, start);
        }
    }

    printList(start);
    freeList(start);
    return 0;
} 
