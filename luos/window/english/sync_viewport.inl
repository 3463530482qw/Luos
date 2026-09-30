namespace Gnik_luos {
    // 视口 = 窗口里的最大内接矩形,输入量按"用的时候现取"从宿主窗口读:
    // 不落下任何指向窗口成员的指针,也不会拿到构造期的旧快照
    // 定义放窗口模块:这里 Window 才完整
    void Window_vulkan::update_viewport() {
        Viewport_input input;
        if (host != nullptr) {
            input.window_width = host->width;
            input.window_height = host->height;
            input.logic_width = host->logic_width;
            input.logic_height = host->logic_height;
            input.aspectratio = host->aspectratio;
        }
        viewport.rebuild(input);
    }
}
