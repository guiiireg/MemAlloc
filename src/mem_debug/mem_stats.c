/**
 * ============================================================================
 * MEMORY ALLOCATOR - Statistics Collection
 * ============================================================================
 * 
 * This file implements statistics collection and display functions
 * for the memory allocator.
 * 
 * ============================================================================
 */

#include "../../include/mem_alloc.h"
#include "../../include/mem_utils.h"
#include <stdio.h>
#include <string.h>

static void calculate_heap_metrics(mem_stats_t *stats)
{
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

void mem_get_stats(mem_stats_t *stats)
{
    if (stats == NULL) {
        return;
    }
    
    memcpy(stats, &global_stats, sizeof(mem_stats_t));
    calculate_heap_metrics(stats);
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
