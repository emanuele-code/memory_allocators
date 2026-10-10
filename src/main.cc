#include "arena.h"

#include <iostream>
#include <cstdint>
#include <cassert>




int main() {
    std::cout << "=== ARENA ALLOCATOR TEST SUITE ===\n\n";

    Arena arena(64);
    std::cout << "Arena capacity: " << arena.capacity() << " bytes\n\n";

    // TEST 1: Allocate 5 chars (5 bytes, alignment 1)
    void* p_chars = arena.allocate(5, 1);
    std::uintptr_t addr_chars = reinterpret_cast<std::uintptr_t>(p_chars);

    std::cout << "[TEST 1] Allocated 5 chars:\n";
    std::cout << "  Address: 0x" << std::hex << addr_chars << std::dec << "\n";
    std::cout << "  Used offset: " << arena.used_byte() << " bytes\n";
    assert(p_chars != nullptr);
    assert(arena.used_byte() == 5);

    // TEST 2: Allocate 1 int (4 bytes, alignment 4)
    // 5 bytes currently used -> requires 3 bytes of padding to reach multiple of 4
    void* p_int = arena.allocate(sizeof(int), alignof(int));
    std::uintptr_t addr_int = reinterpret_cast<std::uintptr_t>(p_int);

    std::cout << "\n[TEST 2] Allocated 1 int (alignment 4):\n";
    std::cout << "  Address: 0x" << std::hex << addr_int << std::dec << "\n";
    std::cout << "  Used offset: " << arena.used_byte() << " bytes (includes 3B padding)\n";
    assert(p_int != nullptr);
    assert(addr_int % alignof(int) == 0);
    assert(arena.used_byte() == 12); // 5 + 3 (pad) + 4 = 12

    // TEST 3: Allocate 1 double (8 bytes, alignment 8)
    // Offset is at 12 (0x0C) -> requires 4 bytes of padding to reach multiple of 8 (0x10)
    void* p_double = arena.allocate(sizeof(double), alignof(double));
    std::uintptr_t addr_double = reinterpret_cast<std::uintptr_t>(p_double);

    std::cout << "\n[TEST 3] Allocated 1 double (alignment 8):\n";
    std::cout << "  Address: 0x" << std::hex << addr_double << std::dec << "\n";
    std::cout << "  Used offset: " << arena.used_byte() << " bytes (includes 4B padding)\n";
    assert(p_double != nullptr);
    assert(addr_double % alignof(double) == 0);
    assert(arena.used_byte() == 24); // 12 + 4 (pad) + 8 = 24

    // TEST 4: Write and read data verification
    int* my_int = static_cast<int*>(p_int);
    *my_int = 123456;

    double* my_double = static_cast<double*>(p_double);
    *my_double = 3.1415926535;

    std::cout << "\n[TEST 4] Memory write/read verification:\n";
    std::cout << "  int value:    " << *my_int << "\n";
    std::cout << "  double value: " << *my_double << "\n";
    assert(*my_int == 123456);
    assert(*my_double == 3.1415926535);

    // TEST 5: Out of bounds allocation (Overflow)
    void* overflow_ptr = arena.allocate(100, 1);
    std::cout << "\n[TEST 5] Out-of-bounds allocation test:\n";
    std::cout << "  Result: " << (overflow_ptr == nullptr ? "nullptr (SUCCESS)" : "FAILED") << "\n";
    assert(overflow_ptr == nullptr);

    // TEST 6: O(1) Reset
    arena.reset();
    std::cout << "\n[TEST 6] arena.reset() invoked:\n";
    std::cout << "  Offset post-reset: " << arena.used_byte() << " bytes\n";
    assert(arena.used_byte() == 0);

    // Reallocate from the beginning
    void* p_new = arena.allocate(sizeof(int), alignof(int));
    std::cout << "  New allocation post-reset at: 0x"
              << std::hex << reinterpret_cast<std::uintptr_t>(p_new) << std::dec << "\n";

    assert(p_new != nullptr);
    assert(arena.used_byte() == sizeof(int));

    std::cout << "\n>>> ALL ASSERTIONS PASSED SUCCESSFULLY! <<<\n";
    return 0;
}
