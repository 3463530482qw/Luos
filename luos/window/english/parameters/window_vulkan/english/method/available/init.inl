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
    }
}