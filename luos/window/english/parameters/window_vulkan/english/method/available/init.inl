namespace Gnik_luos {
    void Window_vulkan::init(Vulkan& vulkan_engine) {
        if (initialized) {
            throw std::runtime_error("Window_vulkan::init => The window vulkan module has been initialized");
        }
        surface.create(*id, vulkan_engine.instance);
        find_graphics_queue_family(vulkan_engine.physical_device);

        vulkan_engine.create_logical_device(graphics_queue_family);
        command_pool.create(vulkan_engine.device, graphics_queue_family);
        initialized = true;

        // 窗口最小化时尺寸为 0,表面尚不可用:交换链留到尺寸恢复后由 rebuild 建立
        if (*pending_width == 0 || *pending_height == 0) {
            rebuild_flag = true;
            return;
        }
        create_swapchain(vulkan_engine);
        rebuild_flag = false;
    }
}
