#include <cstddef>
#include <cstdint> // std::unitptr_t


class Arena {          
    private:
       
        std::byte*  buffer_{nullptr};  // continuous memory allocated
        std::size_t capacity_{0};      // buffer capacity
        std::size_t offset_{0};        // arena offset 

        /* byte alignment to avoid cache line split
         * This function rounds the capacity up to the next multiple of 8 */
        static std::size_t align_up(std::size_t size, std::size_t alignment) {          
            return ( size + (aligment-1) ) & ~(alignment - 1);
        }


    public:
       
        Arena(std::size_t req_capacity) : capacity_(req_capacity) {          
            capacity_ = align_up(req_capacity, alignof(std::max_align_t));   // align to CPU max multiple (8 or 16 byte)
            
            buffer_ = new std::byte[capacity_];                                                                               
            offset_ = 0;
        }

        
        /* +-----+-----+------+
         *  busy | pad | free 
         * +-----+-----+------+
         *             ^ offset */
        void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) {         
            std::byte*    current_ptr  = buffer_ + offset_;

            // convert the ptr in an int to make bitwise operation possible and align it 
            std::uintptr_t current_addr = reinterpret_cast<std::uniptr_t>(current_ptr);
            std::uintptr_t aligned_addr = align_up(current_addr, alignment);

            // convert back to raw bytes the aligned ptr
            std::byte* aligned_ptr = reinterpret_cast<std::byte*>(aligned_addr);
            
            std::size_t next_offset = static_cast<std::size_t>(aligned_ptr- buffer_) + size;
    
            if(next_offset > capacity_) return nullptr;

            offset_ = next_offset;
            return static_cast<void*>(aligned_ptr);
        }

};








