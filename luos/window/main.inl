namespace Gnik_luos {
    Window::Window() {
        *window_vulkan.pending_width = width;
        *window_vulkan.pending_height = height;
    }

    Window::~Window() {
        // 窗口火山持有的表面/交换链等资源随窗口一起回收(火山本体由应用持有,不在此销毁)
        //window_vulkan.destroy();
        close();
    }
}
