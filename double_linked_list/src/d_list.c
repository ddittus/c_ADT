#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <d_list.h>

// Global head pointer
Node *head = NULL;

// Function to create a new node and return its pointer
Node *create_node(void *data) {
    Node *new_node = malloc(sizeof *new_node);
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (head == NULL) {
        head = new_node;
    }
    return new_node;
}

// Function to insert a new node at the head of the list
void insert_at_head(void *data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    if (head != NULL) {
        head->prev = new_node;
        new_node->next = head;
    }
    head = new_node;
}

// Function to insert a new node at the tail of the list
void insert_at_tail(void *data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    if (head == NULL) {
        head = new_node;
        return;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    new_node->prev = current;
}

// Function to print the data of every node in the list
// Uses a function provided by the user as an argument in order to print specific data types.
// For example:
// void print_int(void *data) {
//     int value = *(int *)data;
//     printf("%d ", value);
// }

// int main() {
//     print_all(print_int);
// }
void print_all(void (*print_data)(void *)) {
    Node *current = head;
    while (current != NULL) {
        print_data(current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to delete the node attributed to the given data from the list.
// Uses a pointer to a function provided by the user in order to compare and delete specific data types.
// For example:
// int compare_int(void *node_data, void *search_data) {
//     int node_value = *(int *)node_data;
//     int search_value = *(int *)search_data;
//     return node_value - search_value;
// }

// int main(){
//     int search_value = 3;
//     delete_node(search_value, compare_int);
// }
void delete_node(void *data, int (*compare_data)(void *, void *)) {
    if (head == NULL){
        printf("Head not found.\n");
        return;
    }
    Node *current = head;
    while (current != NULL) {
        if (compare_data(current->data, data) == 0) {
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
        if (current->next == NULL){
            printf("Node was not found.\n");
        }
        current = current->next;
    }
}


// Function to remove and return the head node
Node *pop_head(void) {
    if (head == NULL) {
        return NULL;
    }
    Node *old_head = head;
    head = old_head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    return old_head;
}

// Function to remove and return the tail node
Node *pop_tail(void) {
    if (head == NULL) {
        return NULL;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->prev->next = NULL;
    return current;
}
// Returns the data at the head of the list
void *peek_head(void) {
    if (head == NULL) {
        return NULL;
    }
    return head->data;
}
// Returns the data at the tail of the list
void *peek_tail(void) {
    if (head == NULL) {
        return NULL;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    return current->data;
}
// Returns the data at the given index of the list
void *peek_at(int index) {
    if (head == NULL) {
        return NULL;
    }
    Node *current = head;
    int i;
    for (i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        return NULL;
    }
    return current->data;
}