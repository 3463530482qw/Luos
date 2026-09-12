#pragma once
namespace Gnik_luos {
    class Vulkan_renderpass {
        public:
            vk::raii::RenderPass render_pass{nullptr};
            vk::ClearValue clear_value{vk::ClearColorValue{std::array{0.1f, 0.1f, 0.1f, 1.0f}}};
        public:
            void create(const vk::raii::Device& device, vk::Format format);
    };
    using 渲染通道 = Vulkan_renderpass;
}
