#include "english/parameters/block_name.inl"
#include "english/parameters/slot.inl"
namespace Gnik_luos {
    class Vulkan;
    class Vulkan_texture {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
            #include "english/available/internal/function.inl"
    };
}
#include "english/method/available/main.inl"
#include "english/method/available/layout.inl"
#include "english/method/available/descriptor.inl"
#include "english/method/available/record_barrier.inl"
#include "english/method/available/destroy.inl"
#include "english/method/internal/take.inl"
#include "english/method/internal/create_layout.inl"
#include "english/method/internal/create_slot.inl"
#include "english/method/internal/create_block.inl"
#include "english/method/internal/block_stale.inl"
#include "english/method/internal/read_blocks.inl"
#include "english/method/internal/write_blocks.inl"
#include "english/method/internal/find_memory_type.inl"
