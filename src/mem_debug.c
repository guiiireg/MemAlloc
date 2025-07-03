/**
 * ============================================================================
 * MEMORY ALLOCATOR - Debug and Statistics Module
 * ============================================================================
 * 
 * This file implements debugging features and statistics collection
 * for the memory allocator. Provides memory leak detection, integrity
 * checking, fragmentation analysis, and detailed reporting.
 * 
 * Features:
 * - Memory leak tracking and reporting
 * - Heap integrity validation
 * - Statistics collection and display
 * - Memory usage analysis
 * - Fragmentation calculation
 * - Debug allocation tracking
 * 
 * ============================================================================
 */

#include "../include/mem_alloc.h"
#include "../include/mem_utils.h"
#include <stdio.h>
#include <string.h>

void mem_get_stats(mem_stats_t *stats)
{
    if (stats == NULL) {
        return;
    }
    
    memcpy(stats, &global_stats, sizeof(mem_stats_t));
    
    size_t free_blocks = 0;
    size_t free_memory = 0;
    size_t total_memory = 0;
    
    mem_block_t *current = first_block;
    while (current != NULL) {
        total_memory += current->size + sizeof(mem_block_t);
        if (current->is_free) {
            free_blocks++;
            free_memory += current->size;
        }
        current = current->next;
    }
    
    if (total_memory > 0) {
        stats->fragmentation_ratio = (free_memory * 100) / total_memory;
    }
}

void mem_print_stats(void)
{
    mem_stats_t stats;
    mem_get_stats(&stats);
    
    printf("========================================\n");
    printf("MEMORY ALLOCATOR STATISTICS\n");
    printf("========================================\n");
    printf("Total allocated:    %zu bytes\n", stats.total_allocated);
    printf("Total freed:        %zu bytes\n", stats.total_freed);
    printf("Current usage:      %zu bytes\n", stats.current_usage);
    printf("Peak usage:         %zu bytes\n", stats.peak_usage);
    printf("Number of allocs:   %zu\n", stats.num_allocations);
    printf("Number of frees:    %zu\n", stats.num_frees);
    printf("Active blocks:      %zu\n", stats.num_blocks);
    printf("Fragmentation:      %zu%%\n", stats.fragmentation_ratio);
    printf("========================================\n");
}

void mem_print_heap(void)
{
    if (first_block == NULL) {
        printf("Heap not initialized\n");
        return;
    }
    
    printf("========================================\n");
    printf("HEAP MEMORY LAYOUT\n");
    printf("========================================\n");
    printf("Heap range: %p - %p\n", heap_start, heap_end);
    printf("Heap size:  %ld bytes\n", (char*)heap_end - (char*)heap_start);
    printf("----------------------------------------\n");
    
    mem_block_t *current = first_block;
    int block_num = 0;
    
    while (current != NULL) {
        printf("Block %d: %p\n", block_num++, (void*)current);
        printf("  Size:   %zu bytes\n", current->size);
        printf("  Status: %s\n", current->is_free ? "FREE" : "ALLOCATED");
        printf("  Magic:  0x%08X\n", current->magic);
        printf("  Data:   %p - %p\n", 
               mem_block_to_ptr(current),
               (char*)mem_block_to_ptr(current) + current->size);
        printf("----------------------------------------\n");
        current = current->next;
    }
}

bool mem_check_integrity(void)
{
    if (first_block == NULL) {
        return true;
    }
    
    mem_block_t *current = first_block;
    size_t total_blocks = 0;
    
    while (current != NULL) {
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

void mem_detect_leaks(void)
{
    if (first_block == NULL) {
        return;
    }
    
    mem_block_t *current = first_block;
    bool leaks_found = false;
    
    printf("========================================\n");
    printf("MEMORY LEAK DETECTION\n");
    printf("========================================\n");
    
    while (current != NULL) {
        if (!current->is_free && current->magic == MEM_MAGIC_ALLOCATED) {
            if (!leaks_found) {
                leaks_found = true;
                printf("Memory leaks detected:\n");
                printf("----------------------------------------\n");
            }
            printf("LEAK: %zu bytes at %p\n", 
                   current->size, mem_block_to_ptr(current));
        }
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
