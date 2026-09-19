namespace Gnik_luos {
    Window::Window() {
        // pending 尺寸是借用宿主窗口成员的指针(自动跟随 resize),构造时只绑定,不解引用
        window_vulkan.pending_width = &width;
        window_vulkan.pending_height = &height;
        window_vulkan.id = &id;
        window_vulkan.viewport.aspectratio = &aspectratio;
        window_vulkan.viewport.logic_aspectratio = &logic_aspectratio;
        window_vulkan.viewport.window_width = &width;
        window_vulkan.viewport.window_height = &height;
        window_vulkan.viewport.window_logic_width = &logic_width;
        window_vulkan.viewport.window_logic_height = &logic_height;

        // 相机交给线条渲染用(借用),默认摆在画布中心:正交档下与"画布左上角是世界原点"的老口径等价
        window_vulkan.line_render.camera = &camera;
        camera.canvas_width = static_cast<float>(logic_width);
        camera.canvas_height = static_cast<float>(logic_height);
        camera.x = camera.canvas_width * 0.5f;
        camera.y = camera.canvas_height * 0.5f;

        private_run.push_back([this]() { router(); });
        
    }

    Window::~Window() {
        // 窗口火山持有的表面/交换链等资源随窗口一起回收(火山本体由应用持有,不在此销毁)
        window_vulkan.destroy();
        close();
    }
}
