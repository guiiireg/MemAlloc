/**
 * ============================================================================
 * MEMORY ALLOCATOR - Free Implementation
 * ============================================================================
 * 
 * This file implements the mem_free function with block validation,
 * statistics tracking, and block merging.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"

void mem_free(void *ptr)
{
    if (ptr == NULL) {
        return;
    }
    
    if (!mem_is_valid_ptr(ptr)) {
        return;
    }
    
    mem_block_t *block = mem_ptr_to_block(ptr);
    
    if (block->magic != MEM_MAGIC_ALLOCATED) {
        return;
    }
    
    block->is_free = true;
    block->magic = MEM_MAGIC_FREE;
    
    global_stats.total_freed += block->size;
    global_stats.current_usage -= block->size;
    global_stats.num_frees++;
    
    mem_merge_blocks(block);
}
