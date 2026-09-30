namespace Gnik_luos {
    Window::Window() : camera(window_vulkan.camera), drawer(window_vulkan.drawer) {
        // 相机是窗口的子模块:默认取景的画布尺寸取字段初始值,应用设置配置后会再同步一次
        camera.canvas_width = static_cast<double>(logic_width);
        camera.canvas_height = static_cast<double>(logic_height);

        // 视口量按"用的时候现取"的方式交给 window_vulkan:只交出宿主窗口的位置,不落下成员指针
        window_vulkan.host = this;
        window_vulkan.id = &id;   // 表面创建要窗口句柄:交出成员地址,窗口活多久它就在多久

        private_run.push_back([this]() { router(); });
    }

    Window::~Window() {
        // 窗口火山持有的表面/交换链等资源随窗口一起回收(火山本体由应用持有,不在此销毁)
        window_vulkan.destroy();
        close();
    }
}
