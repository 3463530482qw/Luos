#pragma once
namespace Gnik_luos {
    class Vulkan_swapchain {
        public:
            uint32_t preferred_image_count{0};
            vk::Format format{vk::Format::eUndefined};
            vk::Extent2D extent{0, 0};
            vk::raii::SwapchainKHR swapchain{nullptr};
            std::vector<vk::raii::ImageView> image_views;
        public:
            void reset();
            void create(
                const vk::raii::PhysicalDevice& physical_device,
                const vk::raii::Device& device,
                vk::SurfaceKHR surface,
                uint32_t window_width,
                uint32_t window_height
            );
            void create_image_views(const vk::raii::Device& device);
        private:
            std::vector<vk::Image> images;
    };
    using 交换链 = Vulkan_swapchain;
}
