namespace Gnik_luos {
    void Window::window_resize(float goal_width, float goal_height) {
        width = static_cast<uint32_t>(goal_width);
        height = static_cast<uint32_t>(goal_height);
        // 视口与画布口径跟着新尺寸走(值在用时现取),交换链留到下一帧 draw_frame 里重建
        camera.canvas_width = static_cast<double>(logic_width);
        camera.canvas_height = static_cast<double>(logic_height);
        window_vulkan.update_viewport();
        window_vulkan.request_rebuild();
    }
}
