#include <clay.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

namespace MemoryArena {
    class MemoryArena {
      private:
        size_t m_capacity;
        std::uint8_t* m_buffer;
        size_t m_offset{ 0 };
        static std::size_t align_up(std::size_t addr, std::size_t alignment) {
            std::size_t mask = alignment - 1;
            return (addr + mask) & ~mask;
        }

      public:
        explicit MemoryArena(size_t capacity)
        : m_capacity(capacity), m_buffer(new std::uint8_t[capacity]) {}
        ~MemoryArena() {
            delete[] this->m_buffer;
        };
        // disable copying
        MemoryArena(const MemoryArena&) = delete;
        MemoryArena& operator=(const MemoryArena&) = delete;

        void* alloc(size_t alloc_size, size_t alignment = alignof(std::max_align_t)) {
            size_t curr_mem_addr = reinterpret_cast<size_t>(this->m_buffer) + this->m_offset;
            size_t aligned_mem_addr = align_up(curr_mem_addr, alignment);
            size_t new_offset = (aligned_mem_addr + alloc_size)
                - reinterpret_cast<size_t>(this->m_buffer);

            if (new_offset > this->m_capacity) {
                return nullptr;
            }

            void* ptr = this->m_buffer
                + (aligned_mem_addr - reinterpret_cast<size_t>(this->m_buffer));
            this->m_offset = new_offset;
            return ptr;
        }
        char* alloc_string(const std::string& input_string) {
            size_t len = strlen(input_string.data()) + 1;
            char* allocated_string = (char*)this->alloc(len);
            memcpy(allocated_string, input_string.data(), len);
            return allocated_string;
        }
        Clay_String alloc_clay_string(const std::string& input_string) {
            auto cs = Clay_String{ .length = (std::int32_t)input_string.size(),
                                   .chars = this->alloc_string(input_string) };
            return cs;
        }
        void clear() {
            this->m_offset = 0;
        }
    };
};
