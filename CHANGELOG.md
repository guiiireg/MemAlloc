# Changelog

All notable changes to the MemAlloc custom memory allocator will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-07-03

### Added
- **Core memory allocation functions**
  - Custom `malloc()` implementation with first-fit algorithm
  - Custom `free()` with automatic block merging
  - `realloc()` with in-place resizing when possible
  - `calloc()` with zero-initialization
  
- **Memory management features**
  - Block splitting for optimal memory usage
  - Automatic block merging to reduce fragmentation
  - Memory alignment enforcement (8-byte alignment)
  - Magic number validation for corruption detection
  
- **Debug and analysis tools**
  - Memory leak detection and reporting
  - Heap integrity checking
  - Comprehensive statistics collection
  - Memory usage tracking (current, peak, total)
  - Fragmentation ratio calculation
  
- **Build system**
  - Comprehensive Makefile with 30+ targets
  - Multiple build configurations (debug, release, profile, coverage)
  - Automated dependency management
  - Static and shared library generation
  
- **Testing framework**
  - Complete unit test suite using Criterion
  - 16 comprehensive test cases covering:
    - Basic allocation/deallocation
    - Edge cases and error handling
    - Advanced features (fragmentation, stress testing)
    - Statistics and integrity validation
  
- **Documentation and examples**
  - Detailed README with usage instructions
  - Basic usage example demonstrating core features
  - Advanced example with fragmentation demo and benchmarks
  - Comprehensive API documentation in headers
  - Automated installation script with dependency management
  
- **Memory debugging features**
  - Valgrind integration for memory error detection
  - AddressSanitizer support for debugging builds
  - Memory layout visualization
  - Leak tracking with allocation site information (debug mode)
  
- **Performance features**
  - Optimized release builds with LTO
  - Performance benchmarking against system malloc
  - Memory usage optimization through block coalescing
  - Fast block lookup using doubly-linked lists
  
- **Cross-platform support**
  - POSIX-compliant implementation using mmap
  - Support for Linux, macOS, and other Unix-like systems
  - Configurable heap sizes and memory limits

### Technical Details
- **Memory Model**: Uses mmap for heap allocation instead of sbrk for better portability
- **Data Structure**: Doubly-linked list for block management
- **Alignment**: 8-byte memory alignment for optimal performance
- **Overhead**: 32 bytes per block (metadata + alignment)
- **Magic Numbers**: 0xDEADBEEF (allocated), 0xFEEDFACE (free)
- **Default Heap Size**: 1MB (configurable)
- **Minimum Block Size**: 16 bytes

### Build Configurations
- **Debug**: Full debugging symbols, AddressSanitizer, assertions
- **Release**: -O3 optimization, LTO, no debug info
- **Profile**: Profiling enabled with gprof
- **Coverage**: Code coverage instrumentation for testing

### Supported Platforms
- Linux (tested on Ubuntu 24.04)
- macOS (via Homebrew dependencies)
- Other POSIX-compliant systems

[1.0.0]: https://github.com/username/MemAlloc/releases/tag/v1.0.0
