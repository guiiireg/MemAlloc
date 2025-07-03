/**
 * ============================================================================
 * MEMORY ALLOCATOR - Global Variables and Block Size
 * ============================================================================
 * 
 * This file contains the global variables used throughout the memory allocator
 * and the mem_get_block_size utility function.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"

// Global variables for the memory allocator
void *heap_start = NULL;
void *heap_end = NULL;
mem_block_t *first_block = NULL;
mem_stats_t global_stats = {0};
mem_leak_t *leak_list = NULL;

size_t mem_get_block_size(void *ptr)
{
    if (!mem_is_valid_ptr(ptr)) {
        return 0;
    }
    
    mem_block_t *block = mem_ptr_to_block(ptr);
    return block->size;
}
