#pragma once
#include "english/parameters/vulkan_debug_info/main.hpp"
#include "english/parameters/vulkan_info/main.hpp"
namespace Gnik_luos {
    class Vulkan {
        private:
            vk::raii::Context context;
            std::vector<const char*> layers;
            vk::ValidationFeaturesEXT validation_features;
            vk::DebugUtilsMessengerCreateInfoEXT debug_create_info;
            #ifndef NDEBUG
                vk::raii::DebugUtilsMessengerEXT debug_messenger{nullptr};
            #endif
        public:
            #include "english/available/variable.inl"
            Vulkan_info vulkan_info;
            Vulkan_debug_info& 调试信息{vulkan_info.debug_info};
        public:
            #include "english/available/function.inl"
            #include "中文/可用/函数.inl"
        private:
            #include "english/available/internal/function.inl"
    };
    using 火山 = Vulkan;
}
#include "english/create_instance.inl"
#include "english/create_debug_messenger.inl"
#include "english/collect_validation_features.inl"
#include "english/debug_message_callback.inl"
#include "english/pick_physical_device.inl"
#include "english/rate_physical_device.inl"
#include "english/find_graphics_queue_family.inl"
#include "english/create_logical_device.inl"
#include "english/find_memory_type.inl"
#include "english/init.inl"
