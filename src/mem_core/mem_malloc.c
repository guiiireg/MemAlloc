/**
 * ============================================================================
 * MEMORY ALLOCATOR - Malloc Implementation
 * ============================================================================
 * 
 * This file implements the mem_malloc function with first-fit allocation
 * strategy, block splitting, and statistics tracking.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"
#include <string.h>

static void update_allocation_stats(size_t size)
{
    global_stats.total_allocated += size;
    global_stats.current_usage += size;
    global_stats.num_allocations++;
    
    if (global_stats.current_usage > global_stats.peak_usage) {
        global_stats.peak_usage = global_stats.current_usage;
    }
}

static mem_block_t* prepare_block(mem_block_t *block, size_t size)
{
    if (block->size > size + sizeof(mem_block_t) + MEM_MIN_BLOCK_SIZE) {
        mem_split_block(block, size);
    }
    
    block->is_free = false;
    block->magic = MEM_MAGIC_ALLOCATED;
    return block;
}

void* mem_malloc(size_t size)
{
    if (size == 0) {
        return NULL;
    }
    
    if (heap_start == NULL && mem_init(MEM_HEAP_SIZE) != 0) {
        return NULL;
    }
    
    size = mem_align_size(size);
    mem_block_t *block = mem_find_free_block(size);
    
    if (block == NULL) {
        return NULL;
    }
    
    prepare_block(block, size);
    update_allocation_stats(size);
    
    return mem_block_to_ptr(block);
}
