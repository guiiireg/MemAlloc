/**
 * ============================================================================
 * MEMORY ALLOCATOR - Integrity Checking
 * ============================================================================
 * 
 * This file implements heap integrity validation functions.
 * Validates block structure, magic numbers, and heap consistency.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"
#include <stdio.h>

static bool validate_block(mem_block_t *current)
{
    if (current->magic != MEM_MAGIC_ALLOCATED && current->magic != MEM_MAGIC_FREE) {
        printf("ERROR: Invalid magic number in block %p\n", (void*)current);
        return false;
    }
    
    if ((void*)current < heap_start || (void*)current >= heap_end) {
        printf("ERROR: Block %p outside heap boundaries\n", (void*)current);
        return false;
    }
    
    if (current->next != NULL && current->next->prev != current) {
        printf("ERROR: Broken next/prev link at block %p\n", (void*)current);
        return false;
    }
    
    return true;
}

bool mem_check_integrity(void)
{
    if (first_block == NULL) {
        return true;
    }
    
    mem_block_t *current = first_block;
    size_t total_blocks = 0;
    
    while (current != NULL) {
        if (!validate_block(current)) {
            return false;
        }
        total_blocks++;
        current = current->next;
    }
    
    if (total_blocks != global_stats.num_blocks) {
        printf("ERROR: Block count mismatch. Found: %zu, Expected: %zu\n",
               total_blocks, global_stats.num_blocks);
        return false;
    }
    
    return true;
}
