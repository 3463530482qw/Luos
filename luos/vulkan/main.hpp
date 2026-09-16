#include "english/parameters/vulkan_debug_info/main.hpp"
#include "english/parameters/vulkan_info/main.hpp"
namespace Gnik_luos {
    class Vulkan {
        public: 
            #include "english/available/variable.inl"
        public: 
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
            #include "english/available/internal/function.inl"
    };
    using 火山 = Vulkan;
}
#include "english/method/internal/collect_validation_features.inl"
#include "english/method/internal/debug_message_callback.inl"
#include "english/method/internal/create_debug_messenger.inl"
#include "english/method/internal/create_instance.inl"
#include "english/method/internal/rate_physical_device.inl"
#include "english/method/internal/pick_physical_device.inl"
#include "english/method/available/init.inl"
#include "english/method/available/create_logical_device.inl"