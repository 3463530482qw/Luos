namespace Gnik_luos {
    void Window_vulkan::create_swapchain(Vulkan& vulkan) {
        viewport.rebuild();
        swapchain.create(vulkan.physical_device, vulkan.device);
    }
}