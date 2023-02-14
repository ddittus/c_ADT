#ifndef D_LIST_H
#define D_LIST_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct Node {
    void *data;
    struct Node *prev;
    struct Node *next;
} Node;

/**
 * @brief Create a node object
 * 
 * @param data 
 * @return Node* 
 */
Node *create_node(void *data);

/**
 * @brief Insert given data at the head of the linked list.
 * 
 * @param data 
 */
void insert_at_head(void *data);

/**
 * @brief Function to insert a new node at the tail of the list.
 * 
 * @param data 
 */
void insert_at_tail(void *data);

/**
 * @brief Function to print the data of every node in the list. Uses a function provided by the user as an argument in order to print specific data types.
 * 
 * @param print_data - Function pointer for printing.
 */
void print_all(void (*print_data)(void *));

/**
 * @brief Function to delete the node attributed to the given data from the list. Uses a pointer to a function provided by the user in order to compare and delete specific data types.
 * 
 * @param data 
 * @param compare_data - Function pointer for data comparison.
 */
void delete_node(void *data, int (*compare_data)(void *, void *));

/**
 * @brief Function to remove and return the head node
 * 
 * @return Node* 
 */
Node *pop_head(void);

/**
 * @brief Function to remove and return the tail node
 * 
 * @return Node* 
 */
Node *pop_tail(void);

/**
 * @brief Returns the data at the head of the list
 * 
 * @return void* 
 */
void *peek_head(void);

/**
 * @brief Returns the data at the tail of the list
 * 
 * @return void* 
 */
void *peek_tail(void);

/**
 * @brief Returns the data at the index of the list
 * 
 * @param index 
 * @return void* 
 */
void *peek_at(int index);

#ifdef __cplusplus
}

#endif

#endif