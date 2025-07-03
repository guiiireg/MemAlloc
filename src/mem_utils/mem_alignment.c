/**
 * ============================================================================
 * MEMORY ALLOCATOR - Memory Alignment and Block Finding
 * ============================================================================
 * 
 * This file implements memory alignment calculations and free block
 * finding functions for the memory allocator.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"

size_t mem_align_size(size_t size)
{
    if (size < MEM_MIN_BLOCK_SIZE) {
        size = MEM_MIN_BLOCK_SIZE;
    }
    
    return (size + MEM_ALIGNMENT - 1) & ~(MEM_ALIGNMENT - 1);
}

mem_block_t* mem_find_free_block(size_t size)
{
    mem_block_t *current = first_block;
    
    while (current != NULL) {
        if (current->is_free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}
