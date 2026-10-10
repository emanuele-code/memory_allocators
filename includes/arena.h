#ifndef ARENA_H
#define ARENA_H

#include <cstddef>
#include <cstdint>

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
    void reset() noexcept;

    [[nodiscard]] std::size_t used_byte() const noexcept;
    [[nodiscard]] std::size_t capacity()  const noexcept;
};

#endif // ARENA_H
