/**
 * ============================================================================
 * MEMORY ALLOCATOR - Internal Utilities Header
 * ============================================================================
 * 
 * This file contains internal utility functions and definitions used
 * by the memory allocator implementation. Not exposed to the public API.
 * 
 * Contains:
 * - Block manipulation utilities
 * - Alignment functions
 * - Internal data structure helpers
 * - Memory validation functions
 * 
 * ============================================================================
 */

#ifndef MEM_UTILS_H
#define MEM_UTILS_H

#include "mem_alloc.h"

/* ========================================================================== */
/* INTERNAL UTILITY FUNCTIONS */
/* ========================================================================== */

size_t mem_align_size(size_t size);
mem_block_t* mem_find_free_block(size_t size);
mem_block_t* mem_split_block(mem_block_t *block, size_t size);
void mem_merge_blocks(mem_block_t *block);
bool mem_is_valid_ptr(void *ptr);
void* mem_block_to_ptr(mem_block_t *block);
mem_block_t* mem_ptr_to_block(void *ptr);

/* ========================================================================== */
/* INTERNAL GLOBALS */
/* ========================================================================== */

extern void *heap_start;
extern void *heap_end;
extern mem_block_t *first_block;
extern mem_stats_t global_stats;
extern mem_leak_t *leak_list;

#endif /* MEM_UTILS_H */
