/**
 * ============================================================================
 * MEMORY ALLOCATOR - Initialization and Cleanup
 * ============================================================================
 * 
 * This file implements memory allocator initialization and cleanup functions.
 * Handles heap setup using mmap, initial block creation, and resource cleanup.
 * 
 * Functions:
 * - mem_init: Initialize the memory allocator with specified heap size
 * - mem_cleanup: Clean up allocator resources and unmap memory
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"
#include <sys/mman.h>
#include <string.h>

static int setup_heap(size_t heap_size)
{
    heap_start = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, 
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (heap_start == MAP_FAILED) {
        heap_start = NULL;
        return -1;
    }
    heap_end = (char*)heap_start + heap_size;
    return 0;
}

static void initialize_first_block(size_t heap_size)
{
    first_block = (mem_block_t*)heap_start;
    first_block->size = heap_size - sizeof(mem_block_t);
    first_block->is_free = true;
    first_block->magic = MEM_MAGIC_FREE;
    first_block->next = NULL;
    first_block->prev = NULL;
    
    memset(&global_stats, 0, sizeof(mem_stats_t));
    global_stats.num_blocks = 1;
}

int mem_init(size_t heap_size)
{
    if (heap_start != NULL) {
        return -1;
    }
    
    if (setup_heap(heap_size) != 0) {
        return -1;
    }
    
    initialize_first_block(heap_size);
    return 0;
}

static void cleanup_leak_list(void)
{
    mem_leak_t *leak = leak_list;
    while (leak != NULL) {
        mem_leak_t *next = leak->next;
        leak = next;
    }
    leak_list = NULL;
}

void mem_cleanup(void)
{
    if (heap_start == NULL) {
        return;
    }
    
    size_t heap_size = (char*)heap_end - (char*)heap_start;
    munmap(heap_start, heap_size);
    
    heap_start = NULL;
    heap_end = NULL;
    first_block = NULL;
    memset(&global_stats, 0, sizeof(mem_stats_t));
    
    cleanup_leak_list();
}
