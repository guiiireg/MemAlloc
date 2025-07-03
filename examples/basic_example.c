/**
 * ============================================================================
 * MEMORY ALLOCATOR - Basic Usage Example
 * ============================================================================
 * 
 * This file demonstrates basic usage of the custom memory allocator.
 * Shows simple allocation, deallocation, and memory management operations
 * with statistics reporting.
 * 
 * Demonstrates:
 * - Basic malloc/free operations
 * - Memory statistics collection
 * - Leak detection
 * - Error handling
 * 
 * ============================================================================
 */

#include "../include/mem_alloc.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    printf("========================================\n");
    printf("CUSTOM MEMORY ALLOCATOR - BASIC EXAMPLE\n");
    printf("========================================\n\n");
    
    if (mem_init(1024 * 1024) != 0) {
        printf("Failed to initialize memory allocator\n");
        return 1;
    }
    
    printf("1. Basic allocation and deallocation:\n");
    printf("-------------------------------------\n");
    
    void *ptr1 = mem_malloc(100);
    void *ptr2 = mem_malloc(200);
    void *ptr3 = mem_malloc(300);
    
    printf("Allocated 3 blocks: %p, %p, %p\n", ptr1, ptr2, ptr3);
    
    strcpy((char*)ptr1, "Hello");
    strcpy((char*)ptr2, "World");
    strcpy((char*)ptr3, "Memory Allocator!");
    
    printf("Data in blocks: '%s', '%s', '%s'\n", 
           (char*)ptr1, (char*)ptr2, (char*)ptr3);
    
    mem_free(ptr2);
    printf("Freed middle block\n\n");
    
    printf("2. Memory statistics:\n");
    printf("--------------------\n");
    mem_print_stats();
    printf("\n");
    
    printf("3. Heap layout:\n");
    printf("---------------\n");
    mem_print_heap();
    printf("\n");
    
    printf("4. Reallocation example:\n");
    printf("------------------------\n");
    ptr1 = mem_realloc(ptr1, 500);
    printf("Reallocated first block to 500 bytes: %p\n", ptr1);
    
    strcat((char*)ptr1, " - Extended!");
    printf("Extended data: '%s'\n\n", (char*)ptr1);
    
    printf("5. Calloc example:\n");
    printf("------------------\n");
    int *numbers = (int*)mem_calloc(10, sizeof(int));
    printf("Allocated array of 10 integers (should be zero): ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n\n");
    
    for (int i = 0; i < 10; i++) {
        numbers[i] = i * i;
    }
    printf("Filled with squares: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n\n");
    
    printf("6. Memory leak detection (before cleanup):\n");
    printf("------------------------------------------\n");
    mem_detect_leaks();
    printf("\n");
    
    printf("7. Cleaning up some allocations:\n");
    printf("--------------------------------\n");
    mem_free(ptr1);
    mem_free(numbers);
    printf("Freed some blocks\n\n");
    
    printf("8. Final statistics:\n");
    printf("-------------------\n");
    mem_print_stats();
    printf("\n");
    
    printf("9. Final leak check:\n");
    printf("-------------------\n");
    mem_detect_leaks();
    printf("\n");
    
    printf("10. Integrity check:\n");
    printf("-------------------\n");
    if (mem_check_integrity()) {
        printf("Heap integrity: PASSED\n");
    } else {
        printf("Heap integrity: FAILED\n");
    }
    
    mem_free(ptr3);
    mem_cleanup();
    
    printf("\nExample completed successfully!\n");
    return 0;
}
