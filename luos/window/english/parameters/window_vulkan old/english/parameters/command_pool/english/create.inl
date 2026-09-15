namespace Gnik_luos {
    void Vulkan_command_pool::create(const vk::raii::Device& device, uint32_t graphics_queue_family) {
        // 允许单独重置命令缓冲:每帧重新录制用
        vk::CommandPoolCreateInfo create_info;
        create_info.setQueueFamilyIndex(graphics_queue_family);
        create_info.setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);

        command_pool = vk::raii::CommandPool(device, create_info);
    }
}
