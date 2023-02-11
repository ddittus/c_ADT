#ifndef D_LIST_H
#define D_LIST_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

/**
 * @brief Create a node object
 * 
 * @param data 
 * @return Node* 
 */
Node *create_node(int data);

/**
 * @brief Inserts a node at the head of the linked list.
 * 
 * @param data 
 */
void insert_at_head(int data);

/**
 * @brief Prints all of the nodes in the linked list.
 * 
 */
void print_all();

/**
 * @brief Delete the node from the linked list.
 * 
 * @param data 
 */
void delete_node(int data);

/**
 * @brief Pop off the head of the linked list and return it to the caller.
 * 
 * @return Node* 
 */
Node *pop_head();

/**
 * @brief Pop off the tail of the linked list and return it to the caller.
 * 
 * @return Node* 
 */
Node *pop_tail();

#ifdef __cplusplus
}

#endif

#endif