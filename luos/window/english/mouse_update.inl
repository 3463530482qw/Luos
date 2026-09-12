namespace Gnik_luos {
    void Window::mouse_update(float mouse_x, float mouse_y) {
        mouse.x = std::clamp(
            (mouse_x - static_cast<float>(window_vulkan.viewport.cut_offset_width)) / window_vulkan.viewport.scale,
            0.0f,
            static_cast<float>(logic_width)
        );
        mouse.y = std::clamp(
            (mouse_y - static_cast<float>(window_vulkan.viewport.cut_offset_height)) / window_vulkan.viewport.scale,
            0.0f,
            static_cast<float>(logic_height)
        );
    }
}
