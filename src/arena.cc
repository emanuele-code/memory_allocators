#include "arena.h"

Arena::Arena(std::size_t req_capacity) {
    capacity_ = static_cast<std::size_t>( align_up(req_capacity, alignof(std::max_align_t)) );
   
    buffer_ = new std::byte[capacity_];
    offset_ = 0;
}


Arena::~Arena() {
    delete[] buffer_;
}


void* Arena::allocate(std::size_t size, std::size_t alignment) {
    std::byte* current_ptr = buffer_ + offset_;

    std::uintptr_t current_addr = reinterpret_cast<std::uintptr_t>(current_ptr);
    std::uintptr_t aligned_addr = align_up(current_addr, alignment);

    std::byte* aligned_ptr = reinterpret_cast<std::byte*>(aligned_addr);
    std::size_t next_offset = static_cast<std::size_t>(aligned_ptr - buffer_) + size;

    if (next_offset > capacity_) return nullptr;

    offset_ = next_offset;
    return static_cast<void*>(aligned_ptr);
}


void Arena::reset() noexcept {
    offset_ = 0;
}


std::size_t Arena::used_byte() const noexcept {
    return offset_;
}


std::size_t Arena::capacity() const noexcept {
    return capacity_;
}

