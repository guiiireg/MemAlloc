/**
 * ============================================================================
 * MEMORY ALLOCATOR - Block Merging Functions
 * ============================================================================
 * 
 * This file implements block merging operations for the memory allocator.
 * Combines adjacent free blocks to reduce fragmentation.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"

static void merge_with_next(mem_block_t *block)
{
    if (block->next != NULL && block->next->is_free) {
        block->size += sizeof(mem_block_t) + block->next->size;
        
        if (block->next->next != NULL) {
            block->next->next->prev = block;
        }
        
        block->next = block->next->next;
        global_stats.num_blocks--;
    }
}

static void merge_with_prev(mem_block_t *block)
{
    if (block->prev != NULL && block->prev->is_free) {
        block->prev->size += sizeof(mem_block_t) + block->size;
        
        if (block->next != NULL) {
            block->next->prev = block->prev;
        }
        
        block->prev->next = block->next;
        global_stats.num_blocks--;
    }
}

void mem_merge_blocks(mem_block_t *block)
{
    merge_with_next(block);
    merge_with_prev(block);
}
