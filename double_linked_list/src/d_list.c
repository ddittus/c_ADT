#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

Node *head = NULL;  // global head pointer

// create a new node and return its pointer
Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (head == NULL){
        head = new_node;
    }
    return new_node;
}

// insert a new node at the head of the list
void insert_at_head(int data) {
    Node *new_node = create_node(data);
    if (head == NULL) {
        head = new_node;
        return;
    }
    head->prev = new_node;
    new_node->next = head;
    head = new_node;
}

// print the data of every node in the list
void print_all() {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// delete the node attributed to the data given from the list
bool delete_node(int data) {
    Node *current = head;
    while (current != NULL) {
        if (current->data == data) {
            if (current == head) {
                head = current->next;
                if (head != NULL) {
                    head->prev = NULL;
                }
            } else {
                current->prev->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = current->prev;
                }
            }
            free(current);
            current = NULL;
            break;
        }
        current = current->next;
    }
}

Node *pop_head(){
    Node *old_head = head;
    head = old_head->next;
    return old_head;
}

Node *pop_tail(){
    Node *current = head;

    while (current){
        if (current->next == NULL){
            current->prev->next = NULL;
            return current;
        }
        current = current->next;
    }
    
}