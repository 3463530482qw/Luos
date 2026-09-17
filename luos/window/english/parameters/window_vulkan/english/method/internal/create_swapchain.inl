namespace Gnik_luos {
    void Window_vulkan::create_swapchain(Vulkan& vulkan) {
        viewport.rebuild();
        swapchain.create(vulkan.physical_device, vulkan.device);
        swapchain.create_image_views(vulkan.device);
        renderpass.create(vulkan.device, swapchain.format);
    }
}