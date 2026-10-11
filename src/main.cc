#include "arena.h"

#include <iostream>
#include <cstdint>


int main() {
    std::cout << "=== ARENA ALLOCATOR TEST ===\n\n";

    Arena* arena = new Arena(64); // init the arena
   
  
    /*allocate the memory block you need and evaluate it*/
    int* radius = arena->allocate<int>();
    *radius     = 2;
    std::cout << "Used bytes: " << arena->used_byte() << "\n";

    /*By allocating this block erfore the radius, you save 4 bytes because of memory alignment*/
    double* pi = arena->allocate<double>();
    *pi        = 3.14;
    std::cout << "Used bytes: " << arena->used_byte() << "\n\n";


    const int&    ref_radius = *radius;


    
    arena->reset();
    std::cout << "Reset memory: " << arena->used_byte() << " bytes allocated\n\n";
    
    char* ascii_char = arena->allocate<char>();
    *ascii_char = 'a';
    std::cout << "Used bytes: " << arena->used_byte() << "\n";
   
    const char& ref_ascii = *ascii_char; // even evalutaing with *radius produce the same output
    std::cout << "Ascii value: " << ref_ascii << "\n";


    std::cout << "Destroy the arena\n";
    delete arena;
    arena = nullptr;

    /*previously declared variables became dangling pointers now*/

    return 0;
}
