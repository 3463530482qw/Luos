namespace Gnik_luos {
    void Vulkan_command_buffer::allocate(const vk::raii::Device& device, const vk::raii::CommandPool& command_pool, uint32_t count) {
        command_buffers.clear();

        vk::CommandBufferAllocateInfo allocate_info;
        allocate_info.setCommandPool(*command_pool);
        allocate_info.setLevel(vk::CommandBufferLevel::ePrimary);
        allocate_info.setCommandBufferCount(count);

        command_buffers = vk::raii::CommandBuffers(device, allocate_info);
    }
}
