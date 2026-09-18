namespace Gnik_luos {
    void Window_vulkan::init(Vulkan& vulkan_engine) {
        if (initialized) {
            throw std::runtime_error("Window_vulkan::init => The window vulkan module has been initialized");
        }
        vulkan = &vulkan_engine;   // 借用:火山由应用持有与销毁,窗口火山不负责其生命周期
        surface.create(*id, vulkan->instance);
        find_graphics_queue_family(vulkan->physical_device);

        vulkan->create_logical_device(graphics_queue_family);
        command_pool.create(vulkan->device, graphics_queue_family);
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
