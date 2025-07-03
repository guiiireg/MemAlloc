/**
 * ============================================================================
 * MEMORY ALLOCATOR - Utility Functions
 * ============================================================================
 * 
 * This file implements utility functions for the memory allocator.
 * Contains block manipulation, alignment, validation, and internal
 * helper functions used by the core allocator.
 * 
 * Functions handle:
 * - Memory alignment calculations
 * - Block finding and manipulation
 * - Block splitting and merging operations
 * - Pointer validation and conversion
 * - Internal data structure management
 * 
 * ============================================================================
 */

#include "../include/mem_alloc.h"
#include "../include/mem_utils.h"
#include <stdio.h>

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

mem_block_t* mem_split_block(mem_block_t *block, size_t size)
{
    if (block->size <= size + sizeof(mem_block_t)) {
        return NULL;
    }
    
    mem_block_t *new_block = (mem_block_t*)((char*)block + sizeof(mem_block_t) + size);
    new_block->size = block->size - size - sizeof(mem_block_t);
    new_block->is_free = true;
    new_block->magic = MEM_MAGIC_FREE;
    new_block->next = block->next;
    new_block->prev = block;
    
    if (block->next != NULL) {
        block->next->prev = new_block;
    }
    
    block->next = new_block;
    block->size = size;
    
    global_stats.num_blocks++;
    
    return new_block;
}

void mem_merge_blocks(mem_block_t *block)
{
    if (block->next != NULL && block->next->is_free) {
        block->size += sizeof(mem_block_t) + block->next->size;
        
        if (block->next->next != NULL) {
            block->next->next->prev = block;
        }
        
        block->next = block->next->next;
        global_stats.num_blocks--;
    }
    
    if (block->prev != NULL && block->prev->is_free) {
        block->prev->size += sizeof(mem_block_t) + block->size;
        
        if (block->next != NULL) {
            block->next->prev = block->prev;
        }
        
        block->prev->next = block->next;
        global_stats.num_blocks--;
    }
}

bool mem_is_valid_ptr(void *ptr)
{
    if (ptr == NULL) {
        return false;
    }
    
    if (ptr < heap_start || ptr >= heap_end) {
        return false;
    }
    
    mem_block_t *block = mem_ptr_to_block(ptr);
    
    if ((void*)block < heap_start || (void*)block >= heap_end) {
        return false;
    }
    
    return (block->magic == MEM_MAGIC_ALLOCATED || block->magic == MEM_MAGIC_FREE);
}

void* mem_block_to_ptr(mem_block_t *block)
{
    return (char*)block + sizeof(mem_block_t);
}

mem_block_t* mem_ptr_to_block(void *ptr)
{
    return (mem_block_t*)((char*)ptr - sizeof(mem_block_t));
}
