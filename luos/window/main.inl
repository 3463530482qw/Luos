namespace Gnik_luos {
    Window::Window() {
        // 窗口火山回指宿主:宽度/高度/画布比例/逻辑宽都从窗口自身取,初始化接口因此只剩一个参数
        window_vulkan.host = this;
    }

    Window::~Window() {
        // 窗口火山持有的表面/交换链等资源随窗口一起回收(火山本体由应用持有,不在此销毁)
        window_vulkan.destroy();
        close();
    }
}
