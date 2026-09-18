namespace Gnik_luos {
    void Window::window_resize(float goal_width, float goal_height) {
        width = static_cast<uint32_t>(goal_width);
        height = static_cast<uint32_t>(goal_height);
        window_vulkan.viewport.rebuild();      // 鼠标换算与视口矩形立刻跟上新尺寸
        window_vulkan.request_rebuild();       // 交换链留到下一帧 draw_frame 里重建
    }
}
