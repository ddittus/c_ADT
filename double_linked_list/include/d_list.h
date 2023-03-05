#ifndef D_LIST_H
#define D_LIST_H

#include "error_handler.h"

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
 * @param out_node 
 * @param data 
 * @return ErrorCode 
 */
Node *create_node(void *data);

/**
 * @brief Insert given data at the head of the linked list.
 * 
 * @param data 
 * @return ErrorCode 
 */
ErrorCode insert_at_head(void *data);

/**
 * @brief Function to insert a new node at the tail of the list.
 * 
 * @param data 
 * @return ErrorCode 
 */
ErrorCode insert_at_tail(void *data);

/**
 * @brief Function to insert a new node at the given position.
 * 
 * @param data 
 * @param position 
 * @return ErrorCode 
 */
ErrorCode insert_at_position(void *data, int position);

/**
 * @brief Function to print the data of every node in the list. Uses a function provided by the user as an argument in order to print specific data types.
 * 
 * @param print_data 
 */
void print_all(void (*print_data)(void *));

/**
 * @brief Function to delete the node attributed to the given data from the list. Uses a pointer to a function provided by the user in order to compare and delete specific data types.
 * 
 * @param data 
 * @param compare_data 
 * @return ErrorCode 
 */
ErrorCode delete_node(void *data, int (*compare_data)(void *, void *));

/**
 * @brief Sets the out_node to the head node.
 * 
 * @param out_node 
 * @return ErrorCode 
 */
ErrorCode pop_head(Node **out_node);

/**
 * @brief Sets the out_node to the tail node.
 * 
 * @param out_node 
 * @return ErrorCode 
 */
ErrorCode pop_tail(Node **out_node);

/**
 * @brief Sets the out_data equal to the data of the head node.
 * 
 * @param out_data 
 * @return ErrorCode 
 */
ErrorCode peek_head(void **out_data);

/**
 * @brief Sets the out_data equal to the data of the tail node.
 * 
 * @param out_data 
 * @return ErrorCode 
 */
ErrorCode peek_tail(void **out_data);

/**
 * @brief Sets the out_data equal to the data at the given index.
 * 
 * @param index 
 * @param out_data 
 * @return ErrorCode 
 */
ErrorCode peek_at(int index, void **out_data);

/**
 * @brief Sets the out_length equal to the length of the linked list.
 * 
 * @param out_length 
 * @return ErrorCode 
 */
ErrorCode list_length(int *out_length);

#ifdef __cplusplus
}

#endif

#endif