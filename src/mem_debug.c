/**
 * ============================================================================
 * MEMORY ALLOCATOR - Debug Module Main File
 * ============================================================================
 * 
 * This file serves as the main entry point for the debug module.
 * All debug functions are now organized in separate files in the
 * mem_debug/ subdirectory for better modularity.
 * 
 * Debug module organization:
 * - mem_stats.c: Statistics collection and display
 * - mem_heap_display.c: Heap layout visualization  
 * - mem_integrity.c: Heap integrity validation
 * - mem_leak_detection.c: Memory leak detection
 * - mem_debug_utils.c: Debug utilities and tools
 * 
 * ============================================================================
 */

#include "../include/mem_alloc.h"

__attribute__((unused)) static void _mem_debug_module_placeholder(void)
{
    // This function exists only to prevent compiler warnings
    // about empty translation units. All debug functionality
    // is implemented in the mem_debug/ subdirectory.
}
