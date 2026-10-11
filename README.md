# Arena

A modular C++20 memory arena allocator designed for fast, cache-friendly contiguous allocations with minimal overhead.

## Project Structure

```text
├── includes/        # Header files
├── src/             # Source files (arena.cc, main.cc)
├── Makefile         # Build configuration
├── LICENSE          # License terms
└── .gitignore       # Build artifacts (*.o, arena)
```

## Use Cases

* **Game Engines & Real-Time Systems:** Frame-based or temporary scratchpad allocations where individual deallocations cause unacceptable heap fragmentation.
* **Batch Processing:** Allocating high volumes of small objects that share the same lifecycle and can be freed simultaneously.
* **Deterministic Performance:** Replacing general-purpose `malloc`/`new` calls to avoid lock contention and non-deterministic allocation latency.

## Requirements

* C++20 compatible compiler (`g++` or `clang++`)
* GNU Make

## Build & Run

Compile the binary:
```bash
make
```

Compile and run immediately:
```bash
make run
```

Clean build artifacts and executable:
```bash
make clean
```

## License

This project is licensed under the terms outlined in the [LICENSE](LICENSE) file.