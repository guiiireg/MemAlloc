/**
 * ============================================================================
 * MEMORY ALLOCATOR - Pointer Validation and Conversion
 * ============================================================================
 * 
 * This file implements pointer validation and conversion functions
 * between user pointers and memory blocks.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"

static bool is_ptr_in_heap_bounds(void *ptr)
{
    return ptr >= heap_start && ptr < heap_end;
}

static bool is_block_valid(mem_block_t *block)
{
    if ((void*)block < heap_start || (void*)block >= heap_end) {
        return false;
    }
    
    return (block->magic == MEM_MAGIC_ALLOCATED || block->magic == MEM_MAGIC_FREE);
}

bool mem_is_valid_ptr(void *ptr)
{
    if (ptr == NULL || !is_ptr_in_heap_bounds(ptr)) {
        return false;
    }
    
    mem_block_t *block = mem_ptr_to_block(ptr);
    return is_block_valid(block);
}

void* mem_block_to_ptr(mem_block_t *block)
{
    return (char*)block + sizeof(mem_block_t);
}

mem_block_t* mem_ptr_to_block(void *ptr)
{
    return (mem_block_t*)((char*)ptr - sizeof(mem_block_t));
}
