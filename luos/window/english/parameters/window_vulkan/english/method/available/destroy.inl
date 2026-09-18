namespace Gnik_luos {
    void Window_vulkan::destroy(Vulkan& vulkan_engine) {
        if (!initialized) {
            return;
        }
        initialized = false;

        vulkan_engine.device.waitIdle();
        destroy_resources();
    }
}
