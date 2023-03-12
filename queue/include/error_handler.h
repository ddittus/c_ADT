#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

typedef enum {
  ERROR_SUCCESS,
  ERROR_MEMORY_ALLOCATION,
  ERROR_INVALID_INPUT,
  ERROR_INDEX_OUT_OF_BOUNDS
} ErrorCode;

#define CHECK_ERROR(error_code) do { \
  if (error_code != ERROR_SUCCESS) { \
    printf("Error: %d\n", error_code); \
  } \
} while(0)

#ifdef __cplusplus
}

#endif

#endif