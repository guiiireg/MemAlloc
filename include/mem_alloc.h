/**
 * ============================================================================
 * MEMORY ALLOCATOR - Main Header File
 * ============================================================================
 * 
 * This file provides the main interface for the custom memory allocator.
 * Defines the core allocation and deallocation functions along with
 * memory management utilities and debugging features.
 * 
 * Features:
 * - Custom malloc() and free() implementation
 * - Memory leak detection and reporting
 * - Fragmentation analysis and defragmentation
 * - Memory pool management
 * - Debug and statistics collection
 * 
 * ============================================================================
 */

#ifndef MEM_ALLOC_H
#define MEM_ALLOC_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* ========================================================================== */
/* CONSTANTS AND CONFIGURATION */
/* ========================================================================== */

#define MEM_ALIGNMENT           8
#define MEM_MIN_BLOCK_SIZE      16
#define MEM_HEAP_SIZE           (1024 * 1024)  /* 1MB default heap */
#define MEM_MAX_BLOCKS          1024
#define MEM_MAGIC_ALLOCATED     0xDEADBEEF
#define MEM_MAGIC_FREE          0xFEEDFACE

/* ========================================================================== */
/* DATA STRUCTURES */
/* ========================================================================== */

typedef struct mem_block {
    size_t size;
    bool is_free;
    uint32_t magic;
    struct mem_block *next;
    struct mem_block *prev;
} mem_block_t;

typedef struct mem_stats {
    size_t total_allocated;
    size_t total_freed;
    size_t current_usage;
    size_t peak_usage;
    size_t num_allocations;
    size_t num_frees;
    size_t num_blocks;
    size_t fragmentation_ratio;
} mem_stats_t;

typedef struct mem_leak {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    struct mem_leak *next;
} mem_leak_t;

/* ========================================================================== */
/* CORE ALLOCATION FUNCTIONS */
/* ========================================================================== */

void* mem_malloc(size_t size);
void mem_free(void *ptr);
void* mem_realloc(void *ptr, size_t new_size);
void* mem_calloc(size_t nmemb, size_t size);

/* ========================================================================== */
/* MEMORY MANAGEMENT */
/* ========================================================================== */

int mem_init(size_t heap_size);
void mem_cleanup(void);
void mem_defragment(void);
size_t mem_get_block_size(void *ptr);

/* ========================================================================== */
/* DEBUGGING AND STATISTICS */
/* ========================================================================== */

void mem_get_stats(mem_stats_t *stats);
void mem_print_stats(void);
void mem_print_heap(void);
bool mem_check_integrity(void);
void mem_detect_leaks(void);
void mem_print_leaks(void);

/* ========================================================================== */
/* DEBUG MACROS */
/* ========================================================================== */

#ifdef DEBUG
#define mem_malloc_debug(size, file, line) _mem_malloc_debug(size, file, line)
#define mem_free_debug(ptr, file, line) _mem_free_debug(ptr, file, line)
#define MALLOC(size) mem_malloc_debug(size, __FILE__, __LINE__)
#define FREE(ptr) mem_free_debug(ptr, __FILE__, __LINE__)

void* _mem_malloc_debug(size_t size, const char *file, int line);
void _mem_free_debug(void *ptr, const char *file, int line);
#else
#define MALLOC(size) mem_malloc(size)
#define FREE(ptr) mem_free(ptr)
#endif

#endif /* MEM_ALLOC_H */
