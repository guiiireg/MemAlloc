/**
 * ============================================================================
 * MEMORY ALLOCATOR - Debug Utilities
 * ============================================================================
 * 
 * This file implements utility debug functions including defragmentation
 * and debug allocation tracking.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"
#include <stdio.h>

void mem_defragment(void)
{
    if (first_block == NULL) {
        return;
    }
    
    mem_block_t *current = first_block;
    
    while (current != NULL) {
        if (current->is_free) {
            mem_merge_blocks(current);
        }
        current = current->next;
    }
}

#ifdef DEBUG
void* _mem_malloc_debug(size_t size, const char *file, int line)
{
    void *ptr = mem_malloc(size);
    
    if (ptr != NULL) {
        printf("DEBUG: Allocated %zu bytes at %p (%s:%d)\n", size, ptr, file, line);
    }
    
    return ptr;
}

void _mem_free_debug(void *ptr, const char *file, int line)
{
    if (ptr == NULL) {
        return;
    }
    
    printf("DEBUG: Freeing memory at %p (%s:%d)\n", ptr, file, line);
    mem_free(ptr);
}
#endif
