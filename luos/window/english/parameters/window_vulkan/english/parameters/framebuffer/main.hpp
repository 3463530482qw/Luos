#pragma once
namespace Gnik_luos {
    class Vulkan_framebuffer {
        public:
            std::vector<vk::raii::Framebuffer> framebuffers;
        public:
            void create(
                const vk::raii::Device& device,
                const vk::raii::RenderPass& render_pass,
                const std::vector<vk::raii::ImageView>& image_views,
                vk::Extent2D extent
            );
    };
    using 帧缓冲 = Vulkan_framebuffer;
}
