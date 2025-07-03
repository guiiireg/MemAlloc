/**
 * ============================================================================
 * MEMORY ALLOCATOR - Block Splitting Functions
 * ============================================================================
 * 
 * This file implements block splitting operations for the memory allocator.
 * Handles dividing large blocks into smaller allocated and free sections.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"

static void setup_new_block(mem_block_t *new_block, mem_block_t *block, size_t remaining_size)
{
    new_block->size = remaining_size;
    new_block->is_free = true;
    new_block->magic = MEM_MAGIC_FREE;
    new_block->next = block->next;
    new_block->prev = block;
    
    if (block->next != NULL) {
        block->next->prev = new_block;
    }
    
    block->next = new_block;
}

mem_block_t* mem_split_block(mem_block_t *block, size_t size)
{
    if (block->size <= size + sizeof(mem_block_t)) {
        return NULL;
    }
    
    mem_block_t *new_block = (mem_block_t*)((char*)block + sizeof(mem_block_t) + size);
    size_t remaining_size = block->size - size - sizeof(mem_block_t);
    
    setup_new_block(new_block, block, remaining_size);
    block->size = size;
    global_stats.num_blocks++;
    
    return new_block;
}
