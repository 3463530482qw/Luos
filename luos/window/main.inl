namespace Gnik_luos {
    Window::Window() {
        // pending 尺寸是借用宿主窗口成员的指针(自动跟随 resize),构造时只绑定,不解引用
        window_vulkan.pending_width = &width;
        window_vulkan.pending_height = &height;
        window_vulkan.id = &id;
        private_run.push_back([this]() { router(); });
    }

    Window::~Window() {
        // 窗口火山持有的表面/交换链等资源随窗口一起回收(火山本体由应用持有,不在此销毁)
        //window_vulkan.destroy();
        close();
    }
}
