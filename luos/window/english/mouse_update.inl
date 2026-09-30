namespace Gnik_luos {
    // 光标换算只做"屏幕像素 → 画布坐标":先扣掉窗口内接矩形的灰边偏移,
    // 再按画布缩放折算成世界单位并夹在画布内。第 6.4 条要求窗口层不再穿透火山子模块取数,
    // 所以灰边偏移改由 window_vulkan 暴露一个只读访问器出来
    void Window::mouse_update(float mouse_x, float mouse_y) {
        const double scale = (logic_aspectratio > 0.0f) ? static_cast<double>(logic_aspectratio) : 1.0;
        mouse.x = std::clamp(
            (static_cast<double>(mouse_x) - static_cast<double>(window_vulkan.viewport_origin_x())) / scale,
            0.0,
            static_cast<double>(logic_width)
        );
        mouse.y = std::clamp(
            (static_cast<double>(mouse_y) - static_cast<double>(window_vulkan.viewport_origin_y())) / scale,
            0.0,
            static_cast<double>(logic_height)
        );
    }
}
