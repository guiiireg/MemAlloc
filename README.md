# Custom Memory Allocator - MemAlloc

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)]()
[![License](https://img.shields.io/badge/license-MIT-blue)]()
[![Version](https://img.shields.io/badge/version-1.0.0-blue)]()
[![Maintainer](https://img.shields.io/badge/maintainer-@guiiireg-purple)](https://github.com/guiiireg)

A custom memory manager implemented in pure C, offering advanced memory management features, leak detection, and fragmentation analysis.

---

## 📋 Quick Navigation

- [🎯 Project Objectives](#-project-objectives)
- [🏗️ Architecture](#️-architecture)
- [🚀 Quick Installation](#-quick-installation)
- [🎮 Usage](#-usage)
- [🧪 Testing and Validation](#-testing-and-validation)
- [📊 Technical Features](#-technical-features)
- [🤝 Contributing](#-contributing)
- [📚 Complete Documentation](#-complete-documentation)

---

## 🎯 Project Objectives

This project implements a complete memory manager with:

- **Custom allocation**: Implementation of `malloc()` and `free()`
- **Leak management**: Detection and reporting of memory leaks
- **Defragmentation**: Algorithms to reduce fragmentation
- **Statistical analysis**: Detailed collection of usage metrics
- **Advanced debugging**: Validation and diagnostic tools

## 🏗️ Architecture

```
MemAlloc/
├── src/                        # Main source code
│   ├── mem_core/              # 🔧 Core allocation functions
│   │   ├── mem_malloc.c       #   - Memory allocation
│   │   ├── mem_calloc.c       #   - Zero-initialized allocation
│   │   ├── mem_realloc.c      #   - Block reallocation
│   │   ├── mem_free.c         #   - Memory deallocation
│   │   ├── mem_init.c         #   - Initialization and cleanup
│   │   └── mem_globals.c      #   - Global variables and utilities
│   ├── mem_debug/             # 🐛 Debugging and diagnostics
│   │   ├── mem_stats.c        #   - Statistics collection and display
│   │   ├── mem_heap_display.c #   - Heap layout visualization
│   │   ├── mem_integrity.c    #   - Integrity validation
│   │   ├── mem_leak_detection.c #  - Memory leak detection
│   │   └── mem_debug_utils.c  #   - Debug utilities and defragmentation
│   ├── mem_utils/             # ⚙️ Utilities and block management
│   │   ├── mem_alignment.c    #   - Memory alignment and search
│   │   ├── mem_splitting.c    #   - Block splitting
│   │   ├── mem_merging.c      #   - Adjacent block merging
│   │   └── mem_validation.c   #   - Pointer validation and conversion
│   ├── mem_core.c             # Core module main interface
│   ├── mem_debug.c            # Debug module main interface
│   └── mem_utils.c            # Utils module main interface
├── include/                   # Header files
│   ├── mem_alloc.h           # Public interface
│   └── mem_utils.h           # Internal interface
├── tests/                    # Unit tests (Criterion)
│   └── test_mem_alloc.c      # Complete test suite
├── examples/                 # Usage examples
│   ├── basic_example.c       # Basic usage
│   ├── advanced_example.c    # Advanced features
│   └── project_showcase.c    # Complete demonstration
├── lib/                      # Compiled libraries
├── build/                    # Build files
└── Makefile                 # Complete build system
```

### 🎯 Modular Organization

The project uses a **modular architecture** with short functions (≤ 20 lines) distributed across specialized modules:

#### **📁 Core Module (`mem_core/`)**
Essential memory allocation functions:
- **Allocation**: `mem_malloc()`, `mem_calloc()`, `mem_realloc()`
- **Deallocation**: `mem_free()` with validation and merging
- **Initialization**: `mem_init()` and `mem_cleanup()` for heap management
- **Global state**: Shared variables and base utilities

#### **📁 Debug Module (`mem_debug/`)**  
Diagnostic and analysis tools:
- **Statistics**: Collection and display of usage metrics
- **Visualization**: Detailed memory layout display
- **Integrity**: Heap consistency validation
- **Leaks**: Detection and reporting of unreleased blocks
- **Defragmentation**: Free block merging algorithms

#### **📁 Utils Module (`mem_utils/`)**
Block management utilities:
- **Alignment**: Alignment calculations and free block search
- **Splitting**: Block separation into smaller portions
- **Merging**: Combination of adjacent free blocks
- **Validation**: Pointer verification and block/pointer conversion

## 🚀 Quick Installation

### Automatic Method (Recommended)
```bash
git clone https://github.com/guiiireg/MemAlloc.git
cd MemAlloc
./install.sh
```

### Manual Method
```bash
# Dependencies installation
sudo apt-get install build-essential libcriterion-dev valgrind

# Compilation
make build

# Tests
make test

# Examples
make run-basic
```

> 📖 **Detailed guide**: See [Complete Installation](#-compilation-and-installation) below

## 🎮 Usage

### Basic Usage

```c
#include "mem_alloc.h"

int main() {
    // Manager initialization
    mem_init(1024 * 1024);  // 1MB heap
    
    // Allocation
    void *ptr = mem_malloc(100);
    
    // Usage...
    strcpy((char*)ptr, "Hello World");
    
    // Deallocation
    mem_free(ptr);
    
    // Cleanup
    mem_cleanup();
    return 0;
}
```

### Advanced Features

```c
// Detailed statistics
mem_print_stats();

// Leak detection
mem_detect_leaks();

// Integrity check
if (!mem_check_integrity()) {
    printf("Corruption detected!\n");
}

// Defragmentation
mem_defragment();

// Memory layout display
mem_print_heap();
```

## 🧪 Testing and Validation

### Running Tests

```bash
# Complete unit tests
make test

# Tests with verbose output
make test-verbose

# Tests under Valgrind
make valgrind-test

# Coverage report
make test-coverage
```

### Execution Examples

```bash
# Basic example
make run-basic

# Advanced example with stress test
make run-advanced

# Debug with GDB
make gdb-test
```

## 📊 Technical Features

### 🏗️ Modular Design

The project follows a **modular architecture** with clear separation of responsibilities:

- **Short functions**: All functions ≤ 20 lines for optimal readability
- **Specialized modules**: Each module has a unique and well-defined responsibility
- **Encapsulation**: Clear interfaces between modules via headers
- **Maintainability**: Structure facilitating modifications and extensions

### Implemented Algorithms

- **First-fit allocation**: Search for the first sufficient free block
- **Block splitting**: Block division to optimize usage
- **Block merging**: Adjacent free block fusion
- **Alignment enforcement**: Memory alignment for optimal performance

### Data Structures

```c
typedef struct mem_block {
    size_t size;              // Block size
    bool is_free;             // Block state
    uint32_t magic;           // Magic number for validation
    struct mem_block *next;   // Next block
    struct mem_block *prev;   // Previous block
} mem_block_t;
```

### Collected Statistics

- Total allocated/freed memory
- Current usage and peak usage
- Number of allocations/deallocations
- Fragmentation ratio
- Number of active blocks

### 🔧 Function Organization by Module

#### **Core Functions** (`mem_core/`)
```c
// Main allocation - helper functions for stats and preparation
void* mem_malloc(size_t size);
static void update_allocation_stats();
static mem_block_t* prepare_block();

// Reallocation - helper functions for different cases
void* mem_realloc(void *ptr, size_t new_size);
static void* handle_size_decrease();
static void* handle_size_increase();

// Initialization - helper functions for setup
int mem_init(size_t heap_size);
static int setup_heap();
static void initialize_first_block();
```

#### **Debug Functions** (`mem_debug/`)
```c
// Statistics - metrics calculation
void mem_get_stats(mem_stats_t *stats);
static void calculate_heap_metrics();

// Heap display - helper functions for formatting
void mem_print_heap(void);
static void print_heap_header();
static void print_block_info();

// Integrity - modular validation
bool mem_check_integrity(void);
static bool validate_block();
```

#### **Utility Functions** (`mem_utils/`)
```c
// Block splitting - helper for setup
mem_block_t* mem_split_block();
static void setup_new_block();

// Block merging - directional operations
void mem_merge_blocks(mem_block_t *block);
static void merge_with_next();
static void merge_with_prev();

// Validation - specialized checks
bool mem_is_valid_ptr(void *ptr);
static bool is_ptr_in_heap_bounds();
static bool is_block_valid();
```

### 💡 Modular Architecture Benefits

- **🔍 Readability**: Clearer code with short and focused functions
- **🛠️ Maintainability**: Isolated modifications in specific modules
- **🧪 Testability**: Targeted tests by module and function
- **📈 Scalability**: Easy addition of new features
- **🎯 Specialization**: Each file has a unique responsibility
- **🔧 Easier debugging**: Fast problem localization by module

## 🔧 Development Tools

### Static Analysis

```bash
# Analysis with Cppcheck
make analyze

# Code linting
make lint

# Automatic formatting
make format
```

### Profiling and Benchmarks

```bash
# Build with profiling
make CONFIG=profile examples

# Performance benchmark
make benchmark

# Comparison with system malloc
make run-advanced
```

### Advanced Debugging

```bash
# Debug build with sanitizers
make CONFIG=debug build

# Memory tests with Valgrind
make valgrind-examples

# Interactive debug
make gdb-test
```

## 📈 Performance Metrics

The manager provides detailed metrics:

- **Allocation time**: Latency measurement
- **Fragmentation**: Percentage of fragmented memory
- **Efficiency**: Useful memory/overhead ratio
- **Leaks**: Automatic leak detection

## 🛡️ Security and Validation

### Implemented Protections

- **Magic numbers**: Corruption detection
- **Boundary checking**: Boundary verification
- **Double-free protection**: Prevention of multiple deallocations
- **Invalid pointer detection**: Pointer validation

### Debug Tools

- Debug mode with detailed information
- Allocation tracking with file/line
- Heap integrity validation
- Memory leak reports

## 📚 Documentation

### Documentation Generation

```bash
# Doxygen documentation
make docs

# Manual pages
make man
```

### Header Structure

- `mem_alloc.h`: Complete public interface
- `mem_utils.h`: Internal functions (not exposed)

---

## 📚 Complete Documentation

### 📋 Guides and References
- **[CHANGELOG.md](CHANGELOG.md)** - Version history and updates
- **[LICENSE](LICENSE)** - Project MIT license
- **[PROJECT_SUMMARY.md](PROJECT_SUMMARY.md)** - Complete technical project summary

### 🛠️ Development and Contributing
- **[CONTRIBUTING.md](.github/CONTRIBUTING.md)** - Guide for bug reports and improvement requests
- **[Issue Templates](.github/ISSUE_TEMPLATE/)** - Templates for reporting issues
- **[GitHub Workflows](.github/workflows/)** - Automated CI/CD

### 💡 Practical Examples
- **[examples/basic_example.c](examples/basic_example.c)** - Basic manager usage
- **[examples/advanced_example.c](examples/advanced_example.c)** - Advanced features and benchmarks
- **[examples/project_showcase.c](examples/project_showcase.c)** - Complete capability demonstration

### 🧪 Testing and Validation
- **[tests/test_mem_alloc.c](tests/test_mem_alloc.c)** - Complete unit test suite
- **[Makefile](Makefile)** - Build system with 30+ commands

---

## 🚀 Compilation and Installation

### Prerequisites

- GCC (C99 or newer)
- Make
- Criterion (for unit tests)
- Valgrind (optional, for debugging)

### Criterion Installation

```bash
# Ubuntu/Debian
sudo apt-get install libcriterion-dev

# Arch Linux
sudo pacman -S criterion

# macOS (with Homebrew)
brew install criterion
```

### Detailed Compilation

```bash
# Show complete help
make help

# Debug compilation (default)
make build

# Optimized release compilation
make CONFIG=release static

# Compilation with all libraries
make all-libs

# System installation
sudo make install
```
## 🤝 Contributing

**Important note**: This project does not accept direct code contributions.

### How to help
- 🐛 **Bug reports**: Use [GitHub Issues](https://github.com/guiiireg/MemAlloc/issues) with the appropriate template
- 💡 **Feature requests**: Propose new features via issues
- 🗣️ **Feedback**: Share your usage experience and suggestions
- 📊 **Testing**: Report performance results or use cases

### Maintenance
This project is maintained by [@guiiireg](https://github.com/guiiireg). All bug fixes and new feature implementations are handled by the maintainer to ensure code consistency and quality.

For more details, see [CONTRIBUTING.md](.github/CONTRIBUTING.md).

---

## 📝 License

This project is under MIT license. See the LICENSE file for more details.

## 🏆 Demonstrated Skills

- **🏗️ Modular architecture**: Specialized module design with clear responsibilities
- **📏 Code quality**: Short functions (≤20 lines) for optimal readability
- **🔧 Low-level memory management**: Complete custom allocator implementation
- **🔗 Data structures**: Bidirectional linked lists and advanced block management
- **🎯 Pointers and arithmetic**: Expert pointer manipulation and address calculations
- **🐛 System debugging**: Complete diagnostic tools, validation and leak detection
- **✅ Unit testing**: Exhaustive test suite with Criterion framework
- **⚙️ Build system**: Advanced Makefile with 30+ commands and multiple configurations
- **🚀 Optimization**: Efficient algorithms with measurements and performance analysis
- **📁 Code organization**: Clear modular separation between core, debug and utilities
- **🛡️ Security**: Robust validation with magic numbers and corruption protection

---

**Author**: Custom Memory Allocator  
**Version**: 1.0.0  
**Date**: 2025
