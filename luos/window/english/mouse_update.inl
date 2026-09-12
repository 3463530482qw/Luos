namespace Gnik_luos {
    void Window::mouse_update(float mouse_x, float mouse_y) {
        mouse.x = std::clamp((mouse_x - static_cast<float>(window_vulkan.command_buffer.cut_offset_width)) / logic_aspectratio, 0.0f, static_cast<float>(logic_width));
        mouse.y = std::clamp((mouse_y - static_cast<float>(window_vulkan.command_buffer.viewport_height)) / logic_aspectratio, 0.0f, static_cast<float>(logic_height));
    }
}