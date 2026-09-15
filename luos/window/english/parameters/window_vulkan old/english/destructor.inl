namespace Gnik_luos {
    Window_vulkan::~Window_vulkan() {
        // 显式销毁由 destroy 负责(Window 析构会调用),这里只保证句柄与借用指针不残留
        initialized = false;
        rebuild_flag = false;
        vulkan = nullptr;
        host = nullptr;
    }
}
