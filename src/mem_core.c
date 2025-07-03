/**
 * ============================================================================
 * MEMORY ALLOCATOR - Core Implementation
 * ============================================================================
 * 
 * This file implements the core memory allocation and deallocation functions.
 * Provides a custom malloc() and free() implementation with block management,
 * memory tracking, and basic fragmentation handling.
 * 
 * The allocator uses a doubly-linked list to manage memory blocks and
 * implements first-fit allocation strategy with block splitting and merging.
 * 
 * Key Features:
 * - First-fit allocation algorithm
 * - Block splitting for optimal memory usage
 * - Block merging to reduce fragmentation
 * - Memory alignment enforcement
 * - Magic number validation for corruption detection
 * 
 * ============================================================================
 */

#include "../include/mem_alloc.h"
#include "../include/mem_utils.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>

void *heap_start = NULL;
void *heap_end = NULL;
mem_block_t *first_block = NULL;
mem_stats_t global_stats = {0};
mem_leak_t *leak_list = NULL;

int mem_init(size_t heap_size)
{
    if (heap_start != NULL) {
        return -1;
    }
    
    heap_start = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, 
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (heap_start == MAP_FAILED) {
        heap_start = NULL;
        return -1;
    }
    heap_end = (char*)heap_start + heap_size;
    
    first_block = (mem_block_t*)heap_start;
    first_block->size = heap_size - sizeof(mem_block_t);
    first_block->is_free = true;
    first_block->magic = MEM_MAGIC_FREE;
    first_block->next = NULL;
    first_block->prev = NULL;
    
    memset(&global_stats, 0, sizeof(mem_stats_t));
    global_stats.num_blocks = 1;
    
    return 0;
}

void* mem_malloc(size_t size)
{
    if (size == 0) {
        return NULL;
    }
    
    if (heap_start == NULL) {
        if (mem_init(MEM_HEAP_SIZE) != 0) {
            return NULL;
        }
    }
    
    size = mem_align_size(size);
    mem_block_t *block = mem_find_free_block(size);
    
    if (block == NULL) {
        return NULL;
    }
    
    if (block->size > size + sizeof(mem_block_t) + MEM_MIN_BLOCK_SIZE) {
        mem_split_block(block, size);
    }
    
    block->is_free = false;
    block->magic = MEM_MAGIC_ALLOCATED;
    
    global_stats.total_allocated += size;
    global_stats.current_usage += size;
    global_stats.num_allocations++;
    
    if (global_stats.current_usage > global_stats.peak_usage) {
        global_stats.peak_usage = global_stats.current_usage;
    }
    
    return mem_block_to_ptr(block);
}

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
        if (old_size - new_size >= sizeof(mem_block_t) + MEM_MIN_BLOCK_SIZE) {
            mem_split_block(block, new_size);
        }
        return ptr;
    }
    
    void *new_ptr = mem_malloc(new_size);
    if (new_ptr == NULL) {
        return NULL;
    }
    
    memcpy(new_ptr, ptr, old_size);
    mem_free(ptr);
    
    return new_ptr;
}

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

void mem_cleanup(void)
{
    if (heap_start != NULL) {
        size_t heap_size = (char*)heap_end - (char*)heap_start;
        munmap(heap_start, heap_size);
        heap_start = NULL;
        heap_end = NULL;
        first_block = NULL;
        memset(&global_stats, 0, sizeof(mem_stats_t));
        
        mem_leak_t *leak = leak_list;
        while (leak != NULL) {
            mem_leak_t *next = leak->next;
            leak = next;
        }
        leak_list = NULL;
    }
}

size_t mem_get_block_size(void *ptr)
{
    if (!mem_is_valid_ptr(ptr)) {
        return 0;
    }
    
    mem_block_t *block = mem_ptr_to_block(ptr);
    return block->size;
}
