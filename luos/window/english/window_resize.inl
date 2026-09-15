namespace Gnik_luos {
    void Window::window_resize(float goal_width, float goal_height) {
        width = static_cast<uint32_t>(goal_width);
        height = static_cast<uint32_t>(goal_height);
        // aspectratio 是逻辑画布比例(设定时算定),不随窗口变化:窗口比例改变只会让灰边变宽
        //window_vulkan.viewport.rebuild(width, height, aspectratio, logic_width);
        //window_vulkan.request_rebuild(width, height, aspectratio);
    }
}
