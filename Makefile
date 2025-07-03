# ============================================================================
# MEMORY ALLOCATOR - Comprehensive Makefile
# ============================================================================
# 
# This Makefile provides a complete build system for the custom memory
# allocator project. It includes multiple build configurations, testing,
# debugging, profiling, and documentation generation capabilities.
# 
# Main targets:
# - Library building (static and shared)
# - Example programs compilation
# - Unit testing with Criterion
# - Memory debugging with Valgrind
# - Performance profiling
# - Code analysis and formatting
# 
# ============================================================================

# ============================================================================
# PROJECT CONFIGURATION
# ============================================================================

PROJECT_NAME    := MemAlloc
VERSION         := 1.0.0
AUTHOR          := Custom Memory Allocator

# ============================================================================
# DIRECTORY STRUCTURE
# ============================================================================

SRC_DIR         := src
INC_DIR         := include
LIB_DIR         := lib
TEST_DIR        := tests
EXAMPLE_DIR     := examples
BUILD_DIR       := build
OBJ_DIR         := $(BUILD_DIR)/obj
BIN_DIR         := $(BUILD_DIR)/bin
DOC_DIR         := docs

# ============================================================================
# COMPILER AND FLAGS CONFIGURATION
# ============================================================================

CC              := gcc
AR              := ar
RANLIB          := ranlib

# Base compilation flags
CFLAGS_BASE     := -std=c99 -pedantic -Wall -Wextra -Werror
CFLAGS_BASE     += -Wstrict-prototypes -Wmissing-prototypes
CFLAGS_BASE     += -Wold-style-definition -Wmissing-declarations
CFLAGS_BASE     += -Wredundant-decls -Wnested-externs
CFLAGS_BASE     += -I$(INC_DIR)

# Debug flags
CFLAGS_DEBUG    := $(CFLAGS_BASE) -g3 -O0 -DDEBUG -fsanitize=address
CFLAGS_DEBUG    += -fno-omit-frame-pointer -fstack-protector-strong

# Release flags
CFLAGS_RELEASE  := $(CFLAGS_BASE) -O3 -DNDEBUG -march=native -flto

# Test flags
CFLAGS_TEST     := $(CFLAGS_DEBUG) -lcriterion

# Coverage flags
CFLAGS_COVERAGE := $(CFLAGS_DEBUG) --coverage -fprofile-arcs -ftest-coverage

# Profile flags
CFLAGS_PROFILE  := $(CFLAGS_RELEASE) -pg -g

# Default flags
CFLAGS          := $(CFLAGS_DEBUG)

# Linker flags
LDFLAGS         := 
LDFLAGS_DEBUG   := -fsanitize=address
LDFLAGS_TEST    := -lcriterion
LDFLAGS_COVERAGE:= --coverage

# ============================================================================
# SOURCE FILES
# ============================================================================

SOURCES         := $(wildcard $(SRC_DIR)/*.c)
OBJECTS         := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADERS         := $(wildcard $(INC_DIR)/*.h)

TEST_SOURCES    := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS    := $(TEST_SOURCES:$(TEST_DIR)/%.c=$(OBJ_DIR)/test_%.o)
TEST_BINARIES   := $(TEST_SOURCES:$(TEST_DIR)/%.c=$(BIN_DIR)/%)

EXAMPLE_SOURCES := $(wildcard $(EXAMPLE_DIR)/*.c)
EXAMPLE_BINARIES:= $(EXAMPLE_SOURCES:$(EXAMPLE_DIR)/%.c=$(BIN_DIR)/%)

# ============================================================================
# LIBRARY CONFIGURATION
# ============================================================================

STATIC_LIB      := $(LIB_DIR)/lib$(PROJECT_NAME).a
SHARED_LIB      := $(LIB_DIR)/lib$(PROJECT_NAME).so
SHARED_LIB_VER  := $(SHARED_LIB).$(VERSION)

# ============================================================================
# DEFAULT TARGET
# ============================================================================

.PHONY: all
all: help

# ============================================================================
# HELP SYSTEM
# ============================================================================

.PHONY: help
help:
	@echo "============================================================================"
	@echo "$(PROJECT_NAME) v$(VERSION) - Build System Help"
	@echo "============================================================================"
	@echo ""
	@echo "MAIN TARGETS:"
	@echo "  help              - Show this help message"
	@echo "  build             - Build debug version of the library"
	@echo "  release           - Build optimized release version"
	@echo "  all-libs          - Build both static and shared libraries"
	@echo "  clean             - Remove all build artifacts"
	@echo "  distclean         - Complete cleanup including dependencies"
	@echo ""
	@echo "LIBRARY TARGETS:"
	@echo "  static            - Build static library (.a)"
	@echo "  shared            - Build shared library (.so)"
	@echo "  install           - Install library and headers to system"
	@echo "  uninstall         - Remove installed library and headers"
	@echo ""
	@echo "EXAMPLE TARGETS:"
	@echo "  examples          - Build all example programs"
	@echo "  basic-example     - Build basic usage example"
	@echo "  advanced-example  - Build advanced features example"
	@echo "  run-basic         - Build and run basic example"
	@echo "  run-advanced      - Build and run advanced example"
	@echo "  showcase          - Build project showcase example"
	@echo "  run-showcase      - Build and run project showcase example"
	@echo ""
	@echo "TESTING TARGETS:"
	@echo "  test              - Build and run all unit tests"
	@echo "  test-build        - Build unit tests only"
	@echo "  test-run          - Run existing unit tests"
	@echo "  test-verbose      - Run tests with verbose output"
	@echo "  test-coverage     - Generate code coverage report"
	@echo ""
	@echo "DEBUGGING TARGETS:"
	@echo "  debug             - Build with debug symbols and sanitizers"
	@echo "  valgrind-test     - Run tests under Valgrind"
	@echo "  valgrind-examples - Run examples under Valgrind"
	@echo "  gdb-test          - Debug tests with GDB"
	@echo ""
	@echo "ANALYSIS TARGETS:"
	@echo "  analyze           - Run static code analysis"
	@echo "  profile           - Build with profiling enabled"
	@echo "  benchmark         - Run performance benchmarks"
	@echo "  lint              - Run code linting"
	@echo "  format            - Format code with clang-format"
	@echo ""
	@echo "DOCUMENTATION:"
	@echo "  documentation     - Generate documentation"
	@echo "  man               - Generate man pages"
	@echo ""
	@echo "BUILD CONFIGURATIONS:"
	@echo "  CONFIG=debug      - Debug build (default)"
	@echo "  CONFIG=release    - Release build"
	@echo "  CONFIG=profile    - Profile build"
	@echo "  CONFIG=coverage   - Coverage build"
	@echo ""
	@echo "EXAMPLES:"
	@echo "  make build                    # Build debug library"
	@echo "  make CONFIG=release static    # Build release static library"
	@echo "  make test                     # Run all tests"
	@echo "  make run-basic               # Run basic example"
	@echo "  make valgrind-test           # Test with Valgrind"
	@echo ""
	@echo "============================================================================"

# ============================================================================
# BUILD CONFIGURATION SELECTION
# ============================================================================

ifeq ($(CONFIG), release)
    CFLAGS := $(CFLAGS_RELEASE)
    LDFLAGS := 
    BUILD_TYPE := release
else ifeq ($(CONFIG), profile)
    CFLAGS := $(CFLAGS_PROFILE)
    LDFLAGS := -pg
    BUILD_TYPE := profile
else ifeq ($(CONFIG), coverage)
    CFLAGS := $(CFLAGS_COVERAGE)
    LDFLAGS := $(LDFLAGS_COVERAGE)
    BUILD_TYPE := coverage
else
    CFLAGS := $(CFLAGS_DEBUG)
    LDFLAGS := $(LDFLAGS_DEBUG)
    BUILD_TYPE := debug
endif

# ============================================================================
# DIRECTORY CREATION
# ============================================================================

$(OBJ_DIR) $(BIN_DIR) $(LIB_DIR) $(DOC_DIR):
	@mkdir -p $@

# ============================================================================
# OBJECT FILE COMPILATION
# ============================================================================

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "Compiling $< ($(BUILD_TYPE))"
	@$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "Compiling test $<"
	@$(CC) $(CFLAGS_TEST) -c $< -o $@

# ============================================================================
# LIBRARY TARGETS
# ============================================================================

.PHONY: build
build: static

.PHONY: static
static: $(STATIC_LIB)

$(STATIC_LIB): $(OBJECTS) | $(LIB_DIR)
	@echo "Creating static library $@"
	@$(AR) rcs $@ $(OBJECTS)
	@$(RANLIB) $@
	@echo "Static library created successfully"

.PHONY: shared
shared: $(SHARED_LIB)

$(SHARED_LIB): $(OBJECTS) | $(LIB_DIR)
	@echo "Creating shared library $@"
	@$(CC) -shared -Wl,-soname,$(notdir $(SHARED_LIB_VER)) -o $(SHARED_LIB_VER) $(OBJECTS) $(LDFLAGS)
	@ln -sf $(notdir $(SHARED_LIB_VER)) $@
	@echo "Shared library created successfully"

.PHONY: all-libs
all-libs: static shared

.PHONY: release
release:
	@$(MAKE) CONFIG=release static
	@echo "Release build completed"

# ============================================================================
# EXAMPLE TARGETS
# ============================================================================

.PHONY: examples
examples: $(EXAMPLE_BINARIES)

$(BIN_DIR)/basic_example: $(EXAMPLE_DIR)/basic_example.c $(STATIC_LIB) | $(BIN_DIR)
	@echo "Building basic example"
	@$(CC) $(CFLAGS) $< -L$(LIB_DIR) -l$(PROJECT_NAME) -o $@ $(LDFLAGS)

$(BIN_DIR)/advanced_example: $(EXAMPLE_DIR)/advanced_example.c $(STATIC_LIB) | $(BIN_DIR)
	@echo "Building advanced example"
	@$(CC) $(CFLAGS) $< -L$(LIB_DIR) -l$(PROJECT_NAME) -o $@ $(LDFLAGS)

$(BIN_DIR)/project_showcase: $(EXAMPLE_DIR)/project_showcase.c $(STATIC_LIB) | $(BIN_DIR)
	@echo "Building project showcase"
	@$(CC) $(CFLAGS) $< -L$(LIB_DIR) -l$(PROJECT_NAME) -o $@ $(LDFLAGS)

.PHONY: basic-example
basic-example: $(BIN_DIR)/basic_example

.PHONY: advanced-example  
advanced-example: $(BIN_DIR)/advanced_example

.PHONY: showcase
showcase: $(BIN_DIR)/project_showcase

.PHONY: run-basic
run-basic: $(BIN_DIR)/basic_example
	@echo "Running basic example:"
	@echo "======================"
	@LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH $(BIN_DIR)/basic_example

.PHONY: run-advanced
run-advanced: $(BIN_DIR)/advanced_example
	@echo "Running advanced example:"
	@echo "========================="
	@LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH $(BIN_DIR)/advanced_example

.PHONY: run-showcase
run-showcase: $(BIN_DIR)/project_showcase
	@echo "Running project showcase:"
	@echo "========================"
	@LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH $(BIN_DIR)/project_showcase

# ============================================================================
# TESTING TARGETS
# ============================================================================

.PHONY: test-build
test-build: $(BIN_DIR)/test_mem_alloc

$(BIN_DIR)/test_mem_alloc: $(TEST_DIR)/test_mem_alloc.c $(OBJECTS) | $(BIN_DIR)
	@echo "Building unit tests"
	@$(CC) $(CFLAGS_TEST) $< $(OBJECTS) -o $@ $(LDFLAGS_TEST)

.PHONY: test
test: test-build
	@echo "Running unit tests:"
	@echo "=================="
	@LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH $(BIN_DIR)/test_mem_alloc

.PHONY: test-run
test-run: $(BIN_DIR)/test_mem_alloc
	@LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH $(BIN_DIR)/test_mem_alloc

.PHONY: test-verbose
test-verbose: $(BIN_DIR)/test_mem_alloc
	@echo "Running unit tests (verbose):"
	@echo "============================="
	@LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH $(BIN_DIR)/test_mem_alloc --verbose

.PHONY: test-coverage
test-coverage:
	@echo "Generating coverage report:"
	@echo "=========================="
	@$(MAKE) CONFIG=coverage test-build
	@LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH $(BIN_DIR)/test_mem_alloc
	@gcov $(SOURCES)
	@lcov --capture --directory . --output-file coverage.info
	@genhtml coverage.info --output-directory $(BUILD_DIR)/coverage
	@echo "Coverage report generated in $(BUILD_DIR)/coverage/index.html"

# ============================================================================
# DEBUGGING TARGETS
# ============================================================================

.PHONY: debug
debug:
	@$(MAKE) CONFIG=debug static
	@echo "Debug build completed"

.PHONY: valgrind-test
valgrind-test: test-build
	@echo "Running tests under Valgrind:"
	@echo "============================="
	@LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes $(BIN_DIR)/test_mem_alloc

.PHONY: valgrind-examples
valgrind-examples: examples
	@echo "Running basic example under Valgrind:"
	@echo "====================================="
	@LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH valgrind --tool=memcheck --leak-check=full $(BIN_DIR)/basic_example

.PHONY: gdb-test
gdb-test: test-build
	@echo "Starting GDB with test binary:"
	@echo "============================="
	@LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH gdb $(BIN_DIR)/test_mem_alloc

# ============================================================================
# ANALYSIS TARGETS
# ============================================================================

.PHONY: analyze
analyze:
	@echo "Running static analysis:"
	@echo "======================="
	@cppcheck --enable=all --std=c99 --platform=unix64 $(SRC_DIR)/ $(INC_DIR)/
	@scan-build $(MAKE) CONFIG=debug static

.PHONY: profile
profile:
	@$(MAKE) CONFIG=profile examples
	@echo "Profile build completed"

.PHONY: benchmark
benchmark: $(BIN_DIR)/advanced_example
	@echo "Running performance benchmark:"
	@echo "=============================="
	@LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH $(BIN_DIR)/advanced_example

.PHONY: lint
lint:
	@echo "Running code linting:"
	@echo "===================="
	@splint +posixlib -I$(INC_DIR) $(SOURCES) || true

.PHONY: format
format:
	@echo "Formatting code:"
	@echo "==============="
	@clang-format -i $(SOURCES) $(HEADERS) $(TEST_SOURCES) $(EXAMPLE_SOURCES) || true

# ============================================================================
# DOCUMENTATION TARGETS
# ============================================================================

.PHONY: documentation
documentation: | $(DOC_DIR)
	@echo "Generating documentation:"
	@echo "========================"
	@doxygen Doxyfile || echo "Doxygen not found, skipping documentation generation"

.PHONY: man
man: | $(DOC_DIR)
	@echo "Generating man pages:"
	@echo "===================="
	@mkdir -p $(DOC_DIR)/man
	@echo "Man page generation not implemented yet"

# ============================================================================
# INSTALLATION TARGETS
# ============================================================================

PREFIX ?= /usr/local
LIBDIR := $(PREFIX)/lib
INCDIR := $(PREFIX)/include

.PHONY: install
install: static shared
	@echo "Installing library and headers:"
	@echo "==============================="
	@install -d $(LIBDIR) $(INCDIR)
	@install -m 644 $(STATIC_LIB) $(LIBDIR)/
	@install -m 755 $(SHARED_LIB_VER) $(LIBDIR)/
	@ln -sf $(notdir $(SHARED_LIB_VER)) $(LIBDIR)/$(notdir $(SHARED_LIB))
	@install -m 644 $(HEADERS) $(INCDIR)/
	@ldconfig
	@echo "Installation completed to $(PREFIX)"

.PHONY: uninstall
uninstall:
	@echo "Uninstalling library and headers:"
	@echo "================================="
	@rm -f $(LIBDIR)/lib$(PROJECT_NAME).a
	@rm -f $(LIBDIR)/lib$(PROJECT_NAME).so*
	@rm -f $(addprefix $(INCDIR)/, $(notdir $(HEADERS)))
	@ldconfig
	@echo "Uninstallation completed"

# ============================================================================
# CLEANUP TARGETS
# ============================================================================

.PHONY: clean
clean:
	@echo "Cleaning build artifacts:"
	@echo "========================"
	@rm -rf $(BUILD_DIR)
	@rm -rf $(LIB_DIR)
	@rm -f *.gcov *.gcda *.gcno coverage.info
	@echo "Cleanup completed"

.PHONY: distclean
distclean: clean
	@echo "Deep cleaning:"
	@echo "============="
	@rm -rf $(DOC_DIR)
	@rm -f core vgcore.* *.log
	@echo "Deep cleanup completed"

# ============================================================================
# UTILITY TARGETS
# ============================================================================

.PHONY: info
info:
	@echo "============================================================================"
	@echo "BUILD INFORMATION"
	@echo "============================================================================"
	@echo "Project:        $(PROJECT_NAME) v$(VERSION)"
	@echo "Build type:     $(BUILD_TYPE)"
	@echo "Compiler:       $(CC)"
	@echo "CFLAGS:         $(CFLAGS)"
	@echo "LDFLAGS:        $(LDFLAGS)"
	@echo "Sources:        $(words $(SOURCES)) files"
	@echo "Headers:        $(words $(HEADERS)) files"
	@echo "Tests:          $(words $(TEST_SOURCES)) files"
	@echo "Examples:       $(words $(EXAMPLE_SOURCES)) files"
	@echo "============================================================================"

.PHONY: list-targets
list-targets:
	@echo "Available targets:"
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | grep -E "^[a-zA-Z][^$$#/\t=]*$$"

# ============================================================================
# DEPENDENCY TRACKING
# ============================================================================

-include $(OBJECTS:.o=.d)
-include $(TEST_OBJECTS:.o=.d)

%.d: %.c
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

# ============================================================================
# SPECIAL TARGETS
# ============================================================================

.SUFFIXES:
.SECONDARY:
.DELETE_ON_ERROR:
