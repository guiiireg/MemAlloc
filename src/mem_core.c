/**
 * ============================================================================
 * MEMORY ALLOCATOR - Core Module Index
 * ============================================================================
 * 
 * This file serves as the main entry point for the memory allocator core
 * module. It includes all the modular components and provides a unified
 * interface for the memory allocation functions.
 * 
 * The core functionality is now split across multiple files for better
 * organization and maintainability:
 * - mem_globals.c: Global variables and utility functions
 * - mem_init.c: Initialization and cleanup functions
 * - mem_malloc.c: Memory allocation implementation
 * - mem_free.c: Memory deallocation implementation
 * - mem_realloc.c: Memory reallocation implementation
 * - mem_calloc.c: Zeroed memory allocation implementation
 * 
 * ============================================================================
 */

#include "../include/mem_alloc.h"
#include "../include/mem_utils.h"
