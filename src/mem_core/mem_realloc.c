/**
 * ============================================================================
 * MEMORY ALLOCATOR - Realloc Implementation
 * ============================================================================
 * 
 * This file implements the mem_realloc function with size validation,
 * block resizing, and memory copying when needed.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"
#include <string.h>

static void* handle_size_decrease(mem_block_t *block, size_t new_size, size_t old_size)
{
    if (old_size - new_size >= sizeof(mem_block_t) + MEM_MIN_BLOCK_SIZE) {
        mem_split_block(block, new_size);
    }
    return mem_block_to_ptr(block);
}

static void* handle_size_increase(void *ptr, size_t new_size, size_t old_size)
{
    void *new_ptr = mem_malloc(new_size);
    if (new_ptr == NULL) {
        return NULL;
    }
    
    memcpy(new_ptr, ptr, old_size);
    mem_free(ptr);
    return new_ptr;
}

void* mem_realloc(void *ptr, size_t new_size)
{
    if (ptr == NULL) {
        return mem_malloc(new_size);
    }
    
    if (new_size == 0) {
        mem_free(ptr);
        return NULL;
    }
    
    if (!mem_is_valid_ptr(ptr)) {
        return NULL;
    }
    
    mem_block_t *block = mem_ptr_to_block(ptr);
    size_t old_size = block->size;
    new_size = mem_align_size(new_size);
    
    if (new_size <= old_size) {
        return handle_size_decrease(block, new_size, old_size);
    }
    
    return handle_size_increase(ptr, new_size, old_size);
}
