/**
 * ============================================================================
 * MEMORY ALLOCATOR - Leak Detection
 * ============================================================================
 * 
 * This file implements memory leak detection and reporting functions.
 * Scans heap for unreleased allocated blocks.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"
#include <stdio.h>

static void print_leak_header(void)
{
    printf("========================================\n");
    printf("MEMORY LEAK DETECTION\n");
    printf("========================================\n");
}

static bool process_leak_block(mem_block_t *current, bool *leaks_found)
{
    if (!current->is_free && current->magic == MEM_MAGIC_ALLOCATED) {
        if (!*leaks_found) {
            *leaks_found = true;
            printf("Memory leaks detected:\n");
            printf("----------------------------------------\n");
        }
        printf("LEAK: %zu bytes at %p\n", 
               current->size, mem_block_to_ptr(current));
        return true;
    }
    return false;
}

void mem_detect_leaks(void)
{
    if (first_block == NULL) {
        return;
    }
    
    mem_block_t *current = first_block;
    bool leaks_found = false;
    
    print_leak_header();
    
    while (current != NULL) {
        process_leak_block(current, &leaks_found);
        current = current->next;
    }
    
    if (!leaks_found) {
        printf("No memory leaks detected.\n");
    }
    printf("========================================\n");
}

void mem_print_leaks(void)
{
    mem_detect_leaks();
}
