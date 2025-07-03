# Contributing to MemAlloc

> 📖 **Navigation**: [🏠 Main README](../README.md) | [📋 Changelog](../CHANGELOG.md) | [📊 Technical Summary](../PROJECT_SUMMARY.md)

Thank you for your interest in MemAlloc! While this project doesn't accept direct code contributions, we welcome bug reports, feature requests, and feedback to help improve the project.

## Code of Conduct

This project adheres to a code of conduct that we expect all participants to follow:
- Be respectful and inclusive
- Focus on constructive feedback
- Help create a welcoming environment for all

## How to Help

### Reporting Bugs

1. Check if the bug has already been reported in [Issues](https://github.com/guiiireg/MemAlloc/issues)
2. Use the bug report template when creating a new issue
3. Provide detailed reproduction steps
4. Include system information (OS, compiler version, etc.)

### Suggesting Features

1. Check existing feature requests first
2. Use the feature request template
3. Clearly describe the use case and expected benefit
4. Consider backwards compatibility

### Feedback and Discussion

We also welcome:
- Performance feedback and benchmarks
- Use case discussions
- Documentation improvements suggestions
- General feedback about the project

## Project Maintenance

This project is maintained by [@guiiireg](https://github.com/guiiireg). All bug fixes, feature implementations, and code changes are handled by the maintainer to ensure consistency and quality.

## Testing and Verification

If you encounter issues, you can help by:
- Providing detailed reproduction steps
- Testing with different environments
- Sharing performance data or benchmarks
- Verifying fixes when they are released

## Project Information

### Architecture Overview

```
MemAlloc/
├── src/           # Core implementation
├── include/       # Public headers  
├── tests/         # Unit tests
├── examples/      # Usage examples
├── .github/       # GitHub templates
├── Makefile       # Build system
└── install.sh     # Installation script
```

### Build and Test Commands

```bash
# Install dependencies
./install.sh --deps-only

# Build debug version
make build

# Run all tests
make test

# Memory leak testing
make valgrind-test

# Performance testing
make benchmark

# Code analysis
make analyze
```

### Build Configurations

- `make CONFIG=debug` - Debug build with sanitizers
- `make CONFIG=release` - Optimized release build
- `make CONFIG=profile` - Profiling enabled
- `make CONFIG=coverage` - Code coverage instrumentation

## Getting Help

- Check the [📖 README Principal](../README.md) for basic usage
- Look at [💡 examples/](../examples/) for code examples
- Search existing [🐛 Issues](https://github.com/guiiireg/MemAlloc/issues)
- Create a new issue with the appropriate template

## Project Status

This project is actively maintained by [@guiiireg](https://github.com/guiiireg). Bug reports and feature requests are welcomed and will be addressed by the maintainer.

**Thank you for your interest in MemAlloc!**

---

> 📚 **Plus de documentation** : [README](../README.md) | [Changelog](../CHANGELOG.md) | [Résumé Technique](../PROJECT_SUMMARY.md) | [Exemples](../examples/)
