namespace Gnik_luos {
    Window_vulkan::Window_vulkan() {
        swapchain.surface = &surface.surface;
        swapchain.width = &viewport.width;
        swapchain.height = &viewport.height;
    }

    Window_vulkan::~Window_vulkan() {
        // 显式销毁由 destroy 负责(Window 析构会调用),这里只保证标记不残留
        initialized = false;
        rebuild_flag = false;
    }
}
