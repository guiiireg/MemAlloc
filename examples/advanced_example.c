/**
 * ============================================================================
 * MEMORY ALLOCATOR - Advanced Usage Example
 * ============================================================================
 * 
 * This file demonstrates advanced features of the custom memory allocator
 * including fragmentation handling, stress testing, and performance analysis.
 * 
 * Demonstrates:
 * - Fragmentation creation and mitigation
 * - Stress testing with many allocations
 * - Performance measurement
 * - Advanced debugging features
 * 
 * ============================================================================
 */

#include "../include/mem_alloc.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

static void demonstrate_fragmentation(void);
static void stress_test(void);
static void performance_benchmark(void);

static void demonstrate_fragmentation(void)
{
    printf("========================================\n");
    printf("FRAGMENTATION DEMONSTRATION\n");
    printf("========================================\n");
    
    void *ptrs[20];
    
    printf("1. Allocating 20 blocks of 50 bytes each...\n");
    for (int i = 0; i < 20; i++) {
        ptrs[i] = mem_malloc(50);
        printf("Block %2d: %p\n", i, ptrs[i]);
    }
    
    printf("\n2. Initial statistics:\n");
    mem_print_stats();
    
    printf("\n3. Freeing every other block to create fragmentation...\n");
    for (int i = 1; i < 20; i += 2) {
        mem_free(ptrs[i]);
        ptrs[i] = NULL;
        printf("Freed block %d\n", i);
    }
    
    printf("\n4. Statistics after fragmentation:\n");
    mem_print_stats();
    
    printf("\n5. Heap layout (showing fragmentation):\n");
    mem_print_heap();
    
    printf("\n6. Running defragmentation...\n");
    mem_defragment();
    
    printf("\n7. Statistics after defragmentation:\n");
    mem_print_stats();
    
    printf("\n8. Cleaning up remaining blocks...\n");
    for (int i = 0; i < 20; i += 2) {
        if (ptrs[i] != NULL) {
            mem_free(ptrs[i]);
        }
    }
    
    printf("Fragmentation demonstration completed.\n\n");
}

static void stress_test(void)
{
    printf("========================================\n");
    printf("STRESS TEST\n");
    printf("========================================\n");
    
    const int num_operations = 10000;
    void **ptrs = (void**)malloc(sizeof(void*) * num_operations);
    
    printf("Running %d random allocation/deallocation operations...\n", num_operations);
    
    clock_t start = clock();
    
    srand(time(NULL));
    
    for (int i = 0; i < num_operations; i++) {
        if (i % 1000 == 0) {
            printf("Progress: %d/%d operations\n", i, num_operations);
        }
        
        int operation = rand() % 3;
        
        switch (operation) {
            case 0:
                {
                    size_t size = (rand() % 1000) + 1;
                    ptrs[i] = mem_malloc(size);
                }
                break;
                
            case 1:
                if (i > 0 && ptrs[i-1] != NULL) {
                    mem_free(ptrs[i-1]);
                    ptrs[i-1] = NULL;
                }
                ptrs[i] = NULL;
                break;
                
            case 2:
                if (i > 0 && ptrs[i-1] != NULL) {
                    size_t new_size = (rand() % 1000) + 1;
                    ptrs[i-1] = mem_realloc(ptrs[i-1], new_size);
                }
                ptrs[i] = NULL;
                break;
        }
        
        if (i % 100 == 0) {
            if (!mem_check_integrity()) {
                printf("ERROR: Heap integrity check failed at operation %d\n", i);
                break;
            }
        }
    }
    
    clock_t end = clock();
    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\nStress test completed in %.2f seconds\n", cpu_time);
    
    printf("Cleaning up remaining allocations...\n");
    for (int i = 0; i < num_operations; i++) {
        if (ptrs[i] != NULL) {
            mem_free(ptrs[i]);
        }
    }
    
    free(ptrs);
    
    printf("Final integrity check: %s\n", 
           mem_check_integrity() ? "PASSED" : "FAILED");
    
    printf("Stress test completed.\n\n");
}

static void performance_benchmark(void)
{
    printf("========================================\n");
    printf("PERFORMANCE BENCHMARK\n");
    printf("========================================\n");
    
    const int iterations = 100000;
    clock_t start, end;
    
    printf("Benchmarking %d malloc/free operations...\n", iterations);
    
    start = clock();
    for (int i = 0; i < iterations; i++) {
        void *ptr = mem_malloc(64);
        mem_free(ptr);
    }
    end = clock();
    
    double time_custom = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Custom allocator: %.4f seconds\n", time_custom);
    
    start = clock();
    for (int i = 0; i < iterations; i++) {
        void *ptr = malloc(64);
        free(ptr);
    }
    end = clock();
    
    double time_system = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("System allocator: %.4f seconds\n", time_system);
    
    printf("Performance ratio: %.2fx %s\n", 
           time_custom / time_system,
           time_custom < time_system ? "faster" : "slower");
    
    printf("Performance benchmark completed.\n\n");
}

int main(void)
{
    printf("========================================\n");
    printf("CUSTOM MEMORY ALLOCATOR - ADVANCED EXAMPLE\n");
    printf("========================================\n\n");
    
    if (mem_init(2 * 1024 * 1024) != 0) {
        printf("Failed to initialize memory allocator\n");
        return 1;
    }
    
    demonstrate_fragmentation();
    stress_test();
    performance_benchmark();
    
    printf("Final memory statistics:\n");
    mem_print_stats();
    
    printf("\nFinal leak detection:\n");
    mem_detect_leaks();
    
    mem_cleanup();
    
    printf("Advanced example completed successfully!\n");
    return 0;
}
