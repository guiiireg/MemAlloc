/**
 * ============================================================================
 * MEMORY ALLOCATOR - Unit Tests
 * ============================================================================
 * 
 * This file contains comprehensive unit tests for the memory allocator
 * using the Criterion testing framework. Tests cover all major functionality
 * including allocation, deallocation, reallocation, error handling,
 * and edge cases.
 * 
 * Test Categories:
 * - Basic allocation and deallocation
 * - Memory alignment and size handling
 * - Block splitting and merging
 * - Error conditions and edge cases
 * - Memory leak detection
 * - Statistics and integrity checking
 * 
 * ============================================================================
 */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/mem_alloc.h"
#include "../include/mem_utils.h"

static void setup(void);
static void teardown(void);

static void setup(void)
{
    mem_cleanup();
    mem_init(MEM_HEAP_SIZE);
}

static void teardown(void)
{
    mem_cleanup();
}

TestSuite(basic_allocation, .init = setup, .fini = teardown);
TestSuite(advanced_features, .init = setup, .fini = teardown);
TestSuite(error_handling, .init = setup, .fini = teardown);
TestSuite(statistics, .init = setup, .fini = teardown);

Test(basic_allocation, malloc_free_basic)
{
    void *ptr = mem_malloc(100);
    cr_assert_not_null(ptr, "malloc should return valid pointer");
    
    size_t block_size = mem_get_block_size(ptr);
    cr_assert_geq(block_size, 100, "Block size should be at least requested size");
    
    mem_free(ptr);
    cr_assert(mem_check_integrity(), "Heap should be valid after free");
}

Test(basic_allocation, malloc_zero_size)
{
    void *ptr = mem_malloc(0);
    cr_assert_null(ptr, "malloc(0) should return NULL");
}

Test(basic_allocation, free_null_pointer)
{
    mem_free(NULL);
    cr_assert(mem_check_integrity(), "free(NULL) should not corrupt heap");
}

Test(basic_allocation, multiple_allocations)
{
    void *ptr1 = mem_malloc(50);
    void *ptr2 = mem_malloc(100);
    void *ptr3 = mem_malloc(200);
    
    cr_assert_not_null(ptr1, "First allocation should succeed");
    cr_assert_not_null(ptr2, "Second allocation should succeed");
    cr_assert_not_null(ptr3, "Third allocation should succeed");
    
    cr_assert_neq(ptr1, ptr2, "Pointers should be different");
    cr_assert_neq(ptr2, ptr3, "Pointers should be different");
    cr_assert_neq(ptr1, ptr3, "Pointers should be different");
    
    mem_free(ptr1);
    mem_free(ptr2);
    mem_free(ptr3);
}

Test(basic_allocation, realloc_basic)
{
    void *ptr = mem_malloc(100);
    cr_assert_not_null(ptr, "Initial allocation should succeed");
    
    ptr = mem_realloc(ptr, 200);
    cr_assert_not_null(ptr, "Realloc to larger size should succeed");
    
    ptr = mem_realloc(ptr, 50);
    cr_assert_not_null(ptr, "Realloc to smaller size should succeed");
    
    mem_free(ptr);
}

Test(basic_allocation, calloc_basic)
{
    void *ptr = mem_calloc(10, 20);
    cr_assert_not_null(ptr, "calloc should succeed");
    
    char *data = (char*)ptr;
    for (int i = 0; i < 200; i++) {
        cr_assert_eq(data[i], 0, "calloc should zero-initialize memory");
    }
    
    mem_free(ptr);
}

Test(advanced_features, fragmentation_test)
{
    void *ptrs[10];
    
    for (int i = 0; i < 10; i++) {
        ptrs[i] = mem_malloc(100);
        cr_assert_not_null(ptrs[i], "Allocation %d should succeed", i);
    }
    
    for (int i = 1; i < 10; i += 2) {
        mem_free(ptrs[i]);
    }
    
    mem_defragment();
    cr_assert(mem_check_integrity(), "Heap should be valid after defragmentation");
    
    for (int i = 0; i < 10; i += 2) {
        mem_free(ptrs[i]);
    }
}

Test(advanced_features, large_allocation)
{
    size_t large_size = MEM_HEAP_SIZE / 2;
    void *ptr = mem_malloc(large_size);
    cr_assert_not_null(ptr, "Large allocation should succeed");
    
    mem_free(ptr);
}

Test(advanced_features, stress_test)
{
    const int iterations = 1000;
    void *ptrs[iterations];
    
    for (int i = 0; i < iterations; i++) {
        size_t size = (i % 100) + 1;
        ptrs[i] = mem_malloc(size);
        
        if (i % 10 == 0 && i > 0) {
            mem_free(ptrs[i - 10]);
            ptrs[i - 10] = NULL;
        }
    }
    
    for (int i = 0; i < iterations; i++) {
        if (ptrs[i] != NULL) {
            mem_free(ptrs[i]);
        }
    }
    
    cr_assert(mem_check_integrity(), "Heap should be valid after stress test");
}

Test(error_handling, invalid_pointer_free)
{
    void *invalid_ptr = (void*)0x12345678;
    mem_free(invalid_ptr);
    cr_assert(mem_check_integrity(), "free() with invalid pointer should not corrupt heap");
}

Test(error_handling, double_free)
{
    void *ptr = mem_malloc(100);
    cr_assert_not_null(ptr, "Allocation should succeed");
    
    mem_free(ptr);
    mem_free(ptr);
    
    cr_assert(mem_check_integrity(), "Double free should not corrupt heap");
}

Test(error_handling, realloc_null_pointer)
{
    void *ptr = mem_realloc(NULL, 100);
    cr_assert_not_null(ptr, "realloc(NULL, size) should work like malloc");
    
    mem_free(ptr);
}

Test(error_handling, realloc_zero_size)
{
    void *ptr = mem_malloc(100);
    cr_assert_not_null(ptr, "Initial allocation should succeed");
    
    ptr = mem_realloc(ptr, 0);
    cr_assert_null(ptr, "realloc(ptr, 0) should work like free and return NULL");
}

Test(statistics, stats_tracking)
{
    mem_stats_t stats_before, stats_after;
    
    mem_get_stats(&stats_before);
    
    void *ptr1 = mem_malloc(100);
    void *ptr2 = mem_malloc(200);
    
    mem_get_stats(&stats_after);
    
    cr_assert_eq(stats_after.num_allocations, stats_before.num_allocations + 2,
                 "Allocation count should increase by 2");
    cr_assert_geq(stats_after.total_allocated, stats_before.total_allocated + 300,
                  "Total allocated should increase by at least 300");
    
    mem_free(ptr1);
    mem_free(ptr2);
}

Test(statistics, leak_detection)
{
    void *ptr1 = mem_malloc(100);
    void *ptr2 = mem_malloc(200);
    
    mem_free(ptr1);
    
    mem_detect_leaks();
    
    mem_free(ptr2);
}

Test(statistics, integrity_check)
{
    void *ptr = mem_malloc(100);
    cr_assert_not_null(ptr, "Allocation should succeed");
    
    cr_assert(mem_check_integrity(), "Heap integrity should be valid");
    
    mem_free(ptr);
    cr_assert(mem_check_integrity(), "Heap integrity should remain valid after free");
}
