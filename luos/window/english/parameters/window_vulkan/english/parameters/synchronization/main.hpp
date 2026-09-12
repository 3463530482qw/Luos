#pragma once
namespace Gnik_luos {
    class Vulkan_synchronization {
        public:
            vk::raii::Semaphore image_available{nullptr};
            vk::raii::Semaphore render_finished{nullptr};
            vk::raii::Fence frame_fence{nullptr};
        public:
            void create(const vk::raii::Device& device);
            void wait(const vk::raii::Device& device);
    };
    using 同步对象 = Vulkan_synchronization;
}
