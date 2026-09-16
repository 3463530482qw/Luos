namespace Gnik_luos {
    void Vulkan_command_pool::create(const vk::raii::Device& device, uint32_t graphics_queue_family) {
        vk::CommandPoolCreateInfo create_info;
        create_info.setQueueFamilyIndex(graphics_queue_family);
        create_info.setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);

        command_pool = vk::raii::CommandPool(device, create_info);
    }
}
