namespace Gnik_luos {
    void Vulkan_synchronization::create(const vk::raii::Device& device, uint32_t image_count) {
        // 围栏初始即为已触发,首帧等待才不会死锁
        vk::FenceCreateInfo fence_info;
        fence_info.setFlags(vk::FenceCreateFlagBits::eSignaled);
        frame_fence = vk::raii::Fence(device, fence_info);

        // 取像信号每在途帧一个(单帧在途,一个够用);渲染完成信号每张交换链图像一个 ——
        // 同一信号量跨图像复用会被校验层判为仍在使用(VUID-vkQueueSubmit-pSignalSemaphores-00067)
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
