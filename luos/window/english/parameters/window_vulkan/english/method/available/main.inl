namespace Gnik_luos {
    Window_vulkan::Window_vulkan() {
        swapchain.surface = &surface.surface;
        swapchain.width = &viewport.width;
        swapchain.height = &viewport.height;
    }
}