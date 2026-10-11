#include "arena.h"

#include <iostream>
#include <cstdint>
#include <iomanip>

class TestObj {          
    private:
        int value_{0};
    public:
        TestObj(int value) : value_(value) {}
        
        inline int  get_value() const noexcept { return value_;  }
        inline void set_value(int value)       { value_ = value; }
};


int main() {
    std::cout << "=== ARENA ALLOCATOR TEST ===\n\n";

    Arena* arena = new Arena(128); // init the arena
   
  
    /*allocate the memory block you need and evaluate it*/
    int* radius = arena->allocate<int>();
    *radius     = 2;

    /*By allocating this block erfore the radius, you save 4 bytes because of memory alignment*/
    double* pi = arena->allocate<double>(3.14);
    
    std::cout << "Radius value: " << std::left << std::setw(6) << *radius << "Used bytes: " << arena->used_byte() << "\n";
    std::cout << "Pi value    : " << std::left << std::setw(6) << *pi     << "Used bytes: " << arena->used_byte() << "\n\n";

    arena->reset();
    std::cout << "Reset memory: " << arena->used_byte() << " bytes allocated\n\n";

    char* ascii_char = arena->allocate<char>();
    *ascii_char = 'a';
    std::cout << "Ascii value : " << std::left << std::setw(6) << *ascii_char << "Used bytes: " << arena->used_byte() << "\n";

    TestObj* obj = arena->create<TestObj>(-10);
    std::cout << "Obj value   : " << std::left << std::setw(6) << obj->get_value() << "Used bytes: " << arena->used_byte() << "\n\n";    


    std::cout << "Destroy the arena\n";
    delete arena;
    arena = nullptr;

    /*previously declared variables became dangling pointers now*/

    return 0;
}
