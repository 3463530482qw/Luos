namespace Gnik_luos {
    void Window::window_resize(float goal_width, float goal_height) {
        width = goal_width;
        height = goal_height;
        window_vulkan.command_buffer.viewport_height = static_cast<float>(height) * aspectratio;
        if (static_cast<float>(width) >= window_vulkan.command_buffer.viewport_height) {
            window_vulkan.command_buffer.viewport_width = window_vulkan.command_buffer.viewport_height;
            window_vulkan.command_buffer.viewport_height = window_vulkan.command_buffer.viewport_height / aspectratio;
            window_vulkan.command_buffer.cut_offset_width = (static_cast<float>(width) - window_vulkan.command_buffer.viewport_width) / 2.0f;
            window_vulkan.command_buffer.viewport_height = 0;
        } else {
            window_vulkan.command_buffer.viewport_width = static_cast<float>(width);
            window_vulkan.command_buffer.viewport_height = static_cast<float>(width) * aspectratio;
            window_vulkan.command_buffer.cut_offset_width = 0;
            window_vulkan.command_buffer.viewport_height = (static_cast<float>(height) - window_vulkan.command_buffer.viewport_height) / 2.0f;
        }
        logic_aspectratio = static_cast<float>(window_vulkan.command_buffer.viewport_width) / static_cast<float>(logic_width);
    }
}