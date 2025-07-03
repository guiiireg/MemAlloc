/**
 * ============================================================================
 * MEMORY ALLOCATOR - Heap Display Functions
 * ============================================================================
 * 
 * This file implements heap layout visualization and block information
 * display functions.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"
#include <stdio.h>

static void print_heap_header(void)
{
    printf("========================================\n");
    printf("HEAP MEMORY LAYOUT\n");
    printf("========================================\n");
    printf("Heap range: %p - %p\n", heap_start, heap_end);
    printf("Heap size:  %ld bytes\n", (char*)heap_end - (char*)heap_start);
    printf("----------------------------------------\n");
}

static void print_block_info(mem_block_t *block, int block_num)
{
    printf("Block %d: %p\n", block_num, (void*)block);
    printf("  Size:   %zu bytes\n", block->size);
    printf("  Status: %s\n", block->is_free ? "FREE" : "ALLOCATED");
    printf("  Magic:  0x%08X\n", block->magic);
    printf("  Data:   %p - %p\n", 
           mem_block_to_ptr(block),
           (char*)mem_block_to_ptr(block) + block->size);
    printf("----------------------------------------\n");
}

void mem_print_heap(void)
{
    if (first_block == NULL) {
        printf("Heap not initialized\n");
        return;
    }
    
    print_heap_header();
    
    mem_block_t *current = first_block;
    int block_num = 0;
    
    while (current != NULL) {
        print_block_info(current, block_num++);
        current = current->next;
    }
}
