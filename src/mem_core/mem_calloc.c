/**
 * ============================================================================
 * MEMORY ALLOCATOR - Calloc Implementation
 * ============================================================================
 * 
 * This file implements the mem_calloc function with overflow protection
 * and zero-initialization of allocated memory.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"
#include <string.h>

void* mem_calloc(size_t nmemb, size_t size)
{
    size_t total_size = nmemb * size;

    if (nmemb != 0 && total_size / nmemb != size) {
        return NULL;
    }
    void *ptr = mem_malloc(total_size);
    if (ptr != NULL) {
        memset(ptr, 0, total_size);
    }
    return ptr;
}
