namespace Gnik_luos {
    // 定义放窗口模块:这里 Window 才完整
    Draw& Draw::bind_window(Window& window) {
        private_vertex_sink = &window.window_vulkan.line_render.vertex;
        return *this;
    }
}
