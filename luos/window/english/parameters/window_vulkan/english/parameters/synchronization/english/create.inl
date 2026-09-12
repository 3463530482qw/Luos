namespace Gnik_luos {
    void Vulkan_synchronization::create(const vk::raii::Device& device) {
        vk::SemaphoreCreateInfo semaphore_info;

        // 围栏初始即为已触发,首帧等待才不会死锁
        vk::FenceCreateInfo fence_info;
        fence_info.setFlags(vk::FenceCreateFlagBits::eSignaled);

        image_available = vk::raii::Semaphore(device, semaphore_info);
        render_finished = vk::raii::Semaphore(device, semaphore_info);
        frame_fence = vk::raii::Fence(device, fence_info);
    }
}
