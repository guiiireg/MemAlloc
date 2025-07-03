#!/bin/bash

# ============================================================================
# MEMORY ALLOCATOR - Installation and Setup Script
# ============================================================================
# 
# This script provides automated installation and setup for the MemAlloc
# custom memory allocator project. It handles dependency installation,
# compilation, testing, and optional system installation.
# 
# Usage: ./install.sh [options]
# Options: --help, --deps-only, --test-only, --install, --uninstall
# 
# ============================================================================

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Project information
PROJECT_NAME="MemAlloc"
VERSION="1.0.0"

# Functions
print_header() {
    echo -e "${BLUE}============================================================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}============================================================================${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ $1${NC}"
}

show_help() {
    print_header "$PROJECT_NAME v$VERSION - Installation Script"
    echo ""
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  --help        Show this help message"
    echo "  --deps-only   Install dependencies only"
    echo "  --test-only   Run tests only (requires build)"
    echo "  --install     Install to system (requires sudo)"
    echo "  --uninstall   Remove from system (requires sudo)"
    echo "  --no-tests    Skip running tests during build"
    echo ""
    echo "Examples:"
    echo "  $0                    # Full build and test"
    echo "  $0 --deps-only       # Install dependencies only"
    echo "  $0 --install         # Build and install to system"
    echo "  $0 --uninstall       # Remove from system"
    echo ""
}

check_dependencies() {
    print_header "Checking Dependencies"
    
    local missing_deps=()
    
    # Check for required tools
    if ! command -v gcc &> /dev/null; then
        missing_deps+=("gcc")
    fi
    
    if ! command -v make &> /dev/null; then
        missing_deps+=("make")
    fi
    
    # Check for optional tools
    if ! command -v valgrind &> /dev/null; then
        print_warning "Valgrind not found (optional for memory debugging)"
    fi
    
    if ! command -v doxygen &> /dev/null; then
        print_warning "Doxygen not found (optional for documentation)"
    fi
    
    # Check for Criterion test framework
    if ! pkg-config --exists criterion 2>/dev/null; then
        missing_deps+=("libcriterion-dev")
    fi
    
    if [ ${#missing_deps[@]} -eq 0 ]; then
        print_success "All required dependencies are installed"
        return 0
    else
        print_error "Missing dependencies: ${missing_deps[*]}"
        return 1
    fi
}

install_dependencies() {
    print_header "Installing Dependencies"
    
    if command -v apt-get &> /dev/null; then
        print_info "Detected APT package manager (Debian/Ubuntu)"
        sudo apt-get update
        sudo apt-get install -y build-essential libcriterion-dev valgrind doxygen
    elif command -v pacman &> /dev/null; then
        print_info "Detected Pacman package manager (Arch Linux)"
        sudo pacman -S --needed base-devel criterion valgrind doxygen
    elif command -v dnf &> /dev/null; then
        print_info "Detected DNF package manager (Fedora)"
        sudo dnf install -y gcc make criterion-devel valgrind doxygen
    elif command -v brew &> /dev/null; then
        print_info "Detected Homebrew package manager (macOS)"
        brew install criterion valgrind doxygen
    else
        print_error "Unknown package manager. Please install dependencies manually:"
        echo "  - GCC compiler"
        echo "  - Make build system"
        echo "  - Criterion test framework"
        echo "  - Valgrind (optional)"
        echo "  - Doxygen (optional)"
        exit 1
    fi
    
    print_success "Dependencies installed successfully"
}

build_project() {
    print_header "Building Project"
    
    print_info "Building debug version..."
    make build
    print_success "Debug build completed"
    
    print_info "Building release version..."
    make CONFIG=release all-libs
    print_success "Release build completed"
    
    print_info "Building examples..."
    make examples
    print_success "Examples built"
}

run_tests() {
    print_header "Running Tests"
    
    print_info "Running unit tests..."
    if make test; then
        print_success "All unit tests passed"
    else
        print_error "Some tests failed"
        return 1
    fi
    
    print_info "Running integrity checks..."
    if make run-basic > /dev/null 2>&1; then
        print_success "Basic example runs correctly"
    else
        print_error "Basic example failed"
        return 1
    fi
    
    print_success "All tests completed successfully"
}

install_system() {
    print_header "Installing to System"
    
    if [ "$EUID" -ne 0 ]; then
        print_error "System installation requires root privileges"
        echo "Run with sudo or use --install option"
        exit 1
    fi
    
    make install
    print_success "System installation completed"
    print_info "Library installed to /usr/local/lib"
    print_info "Headers installed to /usr/local/include"
}

uninstall_system() {
    print_header "Uninstalling from System"
    
    if [ "$EUID" -ne 0 ]; then
        print_error "System uninstallation requires root privileges"
        echo "Run with sudo or use --uninstall option"
        exit 1
    fi
    
    make uninstall
    print_success "System uninstallation completed"
}

# Main script logic
main() {
    local deps_only=false
    local test_only=false
    local install_system_flag=false
    local uninstall_system_flag=false
    local skip_tests=false
    
    # Parse command line arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            --help)
                show_help
                exit 0
                ;;
            --deps-only)
                deps_only=true
                shift
                ;;
            --test-only)
                test_only=true
                shift
                ;;
            --install)
                install_system_flag=true
                shift
                ;;
            --uninstall)
                uninstall_system_flag=true
                shift
                ;;
            --no-tests)
                skip_tests=true
                shift
                ;;
            *)
                print_error "Unknown option: $1"
                show_help
                exit 1
                ;;
        esac
    done
    
    # Execute based on options
    if [ "$uninstall_system_flag" = true ]; then
        uninstall_system
        exit 0
    fi
    
    if [ "$test_only" = true ]; then
        run_tests
        exit 0
    fi
    
    # Check and install dependencies if needed
    if ! check_dependencies; then
        if [ "$deps_only" = true ]; then
            install_dependencies
            exit 0
        else
            print_info "Installing missing dependencies..."
            install_dependencies
        fi
    fi
    
    if [ "$deps_only" = true ]; then
        exit 0
    fi
    
    # Build the project
    build_project
    
    # Run tests unless skipped
    if [ "$skip_tests" = false ]; then
        run_tests
    fi
    
    # Install to system if requested
    if [ "$install_system_flag" = true ]; then
        install_system
    fi
    
    print_header "Installation Complete"
    print_success "$PROJECT_NAME v$VERSION is ready to use!"
    echo ""
    print_info "Quick start:"
    echo "  make run-basic      # Run basic example"
    echo "  make run-advanced   # Run advanced example"
    echo "  make test           # Run unit tests"
    echo "  make help           # Show all available commands"
    echo ""
    print_info "Documentation:"
    echo "  README.md           # Project documentation"
    echo "  make documentation  # Generate API docs (requires doxygen)"
    echo ""
}

# Run main function with all arguments
main "$@"
