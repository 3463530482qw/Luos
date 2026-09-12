#pragma once
namespace Gnik_luos {
    class Vulkan_command_buffer {
        public:
            std::vector<vk::raii::CommandBuffer> command_buffers;
        public:
            void allocate(const vk::raii::Device& device, const vk::raii::CommandPool& command_pool, uint32_t count);
            void begin(uint32_t index);
            void begin_render_pass(
                uint32_t index,
                const vk::raii::RenderPass& render_pass,
                const vk::raii::Framebuffer& framebuffer,
                vk::Rect2D render_area,
                vk::ClearValue clear_value
            );
            void set_viewport(uint32_t index, vk::Rect2D viewport_area, vk::Rect2D scissor_area);
            void end(uint32_t index);
    };
    using 命令缓冲 = Vulkan_command_buffer;
}
