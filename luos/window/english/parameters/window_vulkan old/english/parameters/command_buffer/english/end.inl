namespace Gnik_luos {
    void Vulkan_command_buffer::end(uint32_t index) {
        command_buffers[index].endRenderPass();
        command_buffers[index].end();
    }
}
