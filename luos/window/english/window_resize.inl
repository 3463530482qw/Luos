namespace Gnik_luos {
    void Window::window_resize(float goal_width, float goal_height) {
        width = static_cast<uint32_t>(goal_width);
        height = static_cast<uint32_t>(goal_height);

        window_vulkan.viewport.height = static_cast<float>(height) * aspectratio;
        if (static_cast<float>(width) >=  window_vulkan.viewport.width) {
            window_vulkan.viewport.width = window_vulkan.viewport.height;
            window_vulkan.viewport.height = window_vulkan.viewport.height / aspectratio;
            window_vulkan.viewport.cut_offset_width = (static_cast<float>(width) - window_vulkan.viewport.width) / 2.0f;
            window_vulkan.viewport.cut_offset_height = 0;
        } else {
            window_vulkan.viewport.width = static_cast<float>(width);
            window_vulkan.viewport.height = window_vulkan.viewport.width / aspectratio;
            window_vulkan.viewport.cut_offset_height = (static_cast<float>(height) -  window_vulkan.viewport.height) / 2.0f;
            window_vulkan.viewport.cut_offset_width = 0;
        }
        logic_aspectratio = static_cast<float>(window_vulkan.viewport.width) / static_cast<float>(logic_width);
        //wvulkan.framebufferResized = true;
    }
}
