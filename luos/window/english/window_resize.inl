namespace Gnik_luos {
    void Window::window_resize(float goal_width, float goal_height) {
        width = static_cast<uint32_t>(goal_width);
        height = static_cast<uint32_t>(goal_height);
        window_vulkan.viewport.rebuild();
        //window_vulkan.framebufferResized = true;
    }
}
