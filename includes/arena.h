#ifndef ARENA_H
#define ARENA_H

#include <cstddef>
#include <cstdint>
#include <utility> // for std::forward
#include <new>     // for placemente new

class Arena {
private:
    std::byte*  buffer_{nullptr};
    std::size_t capacity_{0};
    std::size_t offset_{0};

    [[nodiscard]] static inline std::uintptr_t align_up(std::uintptr_t addr, std::size_t alignment) noexcept {
        return (addr + (alignment - 1)) & ~(alignment - 1);
    }

public:
    explicit Arena(std::size_t req_capacity);
    ~Arena();

    // Disable copy semantics to prevent double free
    Arena(const Arena&)            = delete;
    Arena& operator=(const Arena&) = delete;

    [[nodiscard]] void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t));
    [[nodiscard]] void* allocate();

    void reset() noexcept;

    [[nodiscard]] std::size_t used_byte() const noexcept;
    [[nodiscard]] std::size_t capacity()  const noexcept;

    template <typename T>
    [[nodiscard]] T* allocate();

    template <typename T>
    [[nodiscard]] T* allocate(const T& value);

    template <typename T, typename ...Args>
    [[nodiscard]] T* create(Args&& ...args);


};


/* Allocate raw memory for primitive types such as: int, char, double, float */
template <typename T>
T* Arena::allocate() {          
    void* mem = allocate(sizeof(T), alignof(T));
    return static_cast<T*>(mem);
}

template <typename T>
T* Arena::allocate(const T& value) {          
    T* ptr = allocate<T>();
    if(ptr != nullptr){           
        *ptr = value;
    } 

    return ptr;
}


/*
 * Creates an object in-place using placement new.
 * Instead of requesting new memory from the heap/system allocator, 
 * this reuses an already aligned chunk from the arena buffer.
 * Thus, the 'new' expression only invokes the object's constructor. 
*/
template <typename T, typename ...Args>
T* Arena::create(Args&& ...args) {
    void* mem = allocate(sizeof(T), alignof(T));
    if(mem == nullptr) return nullptr;

    return new (mem) T(std::forward<Args>(args)...);
}


#endif // ARENA_H
