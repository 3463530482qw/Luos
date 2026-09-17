namespace Gnik_luos {
    void Window_vulkan::init(Vulkan& vulkan) {
        if (initialized) {
            throw std::runtime_error("Window_vulkan::initialize => The window vulkan module has been initialized");
        }
        surface.create(*id, vulkan.instance);
        find_graphics_queue_family(vulkan.physical_device);
        
        vulkan.create_logical_device(graphics_queue_family);
        command_pool.create(vulkan.device, graphics_queue_family);
        initialized = true;

        if (pending_width == 0 || pending_height == 0) {
            rebuild_flag = true;
            return;
        }
        create_swapchain(vulkan);
        rebuild_flag = false;
    }
}