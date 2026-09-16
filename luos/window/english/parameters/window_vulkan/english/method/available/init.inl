namespace Gnik_luos {
    void Window_vulkan::init(Vulkan& vulkan) {
        if (initialized) {
            throw std::runtime_error("Window_vulkan::initialize => The window vulkan module has been initialized");
        }
        surface.create(*id, vulkan.instance);
        initialized = true;
    }
}