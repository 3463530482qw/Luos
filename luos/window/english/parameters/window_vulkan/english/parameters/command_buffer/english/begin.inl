namespace Gnik_luos {
    void Vulkan_command_buffer::begin(uint32_t index) {
        vk::CommandBufferBeginInfo begin_info;
        begin_info.setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

        command_buffers[index].begin(begin_info);
    }
}
