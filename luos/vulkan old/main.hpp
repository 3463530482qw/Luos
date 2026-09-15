#include "english/parameters/vulkan_debug_info/main.hpp"
#include "english/parameters/vulkan_info/main.hpp"
namespace Gnik_luos {
    class Vulkan {
        private:
            #include "english/available/internal/variable.inl"
        public:
            #include "english/available/variable.inl"
            #include "中文/可用/变量.inl"
        public:
            #include "english/available/function.inl"
            #include "中文/可用/函数.inl"
        private:
            #include "english/available/internal/function.inl"
    };
    using 火山 = Vulkan;
}
#include "english/collect_validation_features.inl"
#include "english/create_instance.inl"
#include "english/debug_message_callback.inl"
#include "english/create_debug_messenger.inl"
#include "english/pick_physical_device.inl"
#include "english/rate_physical_device.inl"
#include "english/find_graphics_queue_family.inl"
#include "english/create_logical_device.inl"
#include "english/find_memory_type.inl"
#include "english/init.inl"
