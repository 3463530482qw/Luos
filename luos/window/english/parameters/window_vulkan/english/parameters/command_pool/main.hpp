#pragma once
namespace Gnik_luos {
    class Vulkan_command_pool {
        public:
            vk::raii::CommandPool command_pool{nullptr};
        public:
            void create(const vk::raii::Device& device, uint32_t graphics_queue_family);
    };
    using 命令池 = Vulkan_command_pool;
}
