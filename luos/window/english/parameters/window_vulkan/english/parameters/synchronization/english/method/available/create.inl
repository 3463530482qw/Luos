namespace Gnik_luos {
    void Vulkan_synchronization::create(const vk::raii::Device& device, uint32_t image_count) {
        vk::FenceCreateInfo fence_info;
        fence_info.setFlags(vk::FenceCreateFlagBits::eSignaled);
        frame_fence = vk::raii::Fence(device, fence_info);

        image_available_per_frame.clear();
        render_finished_per_image.clear();
        image_available_per_frame.reserve(1);
        render_finished_per_image.reserve(image_count);
        image_available_per_frame.emplace_back(device, vk::SemaphoreCreateInfo{});
        for (uint32_t index = 0; index < image_count; index++) {
            render_finished_per_image.emplace_back(device, vk::SemaphoreCreateInfo{});
        }
    }
}
