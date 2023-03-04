#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <d_list.h>
#include <error_handler.h>

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
    return new_node;
}

// Function to insert a new node at the head of the list
ErrorCode insert_at_head(void *data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }
    if (head != NULL) {
        head->prev = new_node;
        new_node->next = head;
    }
    head = new_node;
    return ERROR_SUCCESS;
}

// Function to insert a new node at the tail of the list
ErrorCode insert_at_tail(void *data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }
    if (head == NULL) {
        head = new_node;
        return ERROR_SUCCESS;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    new_node->prev = current;
    return ERROR_SUCCESS;
}

// Insert node at given position
ErrorCode insert_at_position(void *data, int position) {
    if (position <= 0) {
        return ERROR_INVALID_INPUT;
    }

    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    int size;
    ErrorCode error = list_length(&size);
    if (error != ERROR_SUCCESS) {
        return error;
    }

    if (position > size + 1) {
        return ERROR_INDEX_OUT_OF_BOUNDS;
    }

    if (head == NULL || position == 1) {
        insert_at_head(data);
        return ERROR_SUCCESS;
    }

    Node *current = head;
    int i;
    for (i = 1; i < position - 1; i++) {
        current = current->next;
    }

    new_node->prev = current;
    new_node->next = current->next;
    if (current->next != NULL) {
        current->next->prev = new_node;
    }
    current->next = new_node;
    return ERROR_SUCCESS;
}

// Function to print the data of every node in the list
// Uses a function provided by the user as an argument in order to print specific data types.
void print_all(void (*print_data)(void *)) {
    if (head == NULL) {
        CHECK_ERROR(ERROR_INVALID_INPUT);
        return;
    }

    Node *current = head;
    while (current != NULL) {
        print_data(current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to delete the node attributed to the given data from the list.
// Uses a pointer to a function provided by the user in order to compare and delete specific data types.
ErrorCode delete_node(void *data, int (*compare_data)(void *, void *)) {
    if (head == NULL) {
        return ERROR_INVALID_INPUT;
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
            return ERROR_SUCCESS;
        }
        current = current->next;
    }
    return ERROR_INVALID_INPUT;
}


// Function to remove and return the head node
ErrorCode pop_head(Node **out_node) {
    if (head == NULL) {
        return ERROR_INVALID_INPUT;
    }
    *out_node = head;
    head = (*out_node)->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    return ERROR_SUCCESS;
}
// Function to remove and return the tail node
ErrorCode pop_tail(Node **out_node) {
  if (head == NULL) {
    return ERROR_INVALID_INPUT;
  }

  Node *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  *out_node = current;
  if (current->prev != NULL) {
    current->prev->next = NULL;
  } else {
    // This is the only node in the list.
    head = NULL;
  }
  return ERROR_SUCCESS;
}

// Returns the data at the head of the list
ErrorCode peek_head(void **out_data) {
    if (head == NULL) {
        return ERROR_INVALID_INPUT;
    }
    *out_data = head->data;
    return ERROR_SUCCESS;
}

// Returns the data at the tail of the list
ErrorCode peek_tail(void **out_data) {
    if (head == NULL) {
        return ERROR_INVALID_INPUT;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    *out_data = current->data;
    return ERROR_SUCCESS;
}

// Returns the data at the given index of the list
ErrorCode peek_at(int index, void **out_data) {
    if (head == NULL) {
        return ERROR_INVALID_INPUT;
    }
    Node *current = head;
    int i;
    for (i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        return ERROR_INVALID_INPUT;
    }
    *out_data = current->data;
    return ERROR_SUCCESS;
}

// Returns the length of the list.
ErrorCode list_length(int *out_length) {
    *out_length = 0;
    if (head == NULL) {
        return ERROR_INVALID_INPUT;
    }
    Node *current = head;
    while (current != NULL) {
        *out_length = *out_length + 1;
        current = current->next;
    }
    return ERROR_SUCCESS;
}