namespace Gnik_luos {
    // 没给尺寸时:按画布比例取显示器 90%(aspectratio 是画布比例,不是窗口当前比例)
    Window& Window::resize() {
        double target_width{};
        double target_height{};
        if ((static_cast<double>(mode->w) / static_cast<double>(mode->h) > static_cast<double>(aspectratio))) {
            target_height = static_cast<double>(mode->h) * 0.9;
            target_width = target_height * static_cast<double>(aspectratio);
        } else {
            target_width = static_cast<double>(mode->w) * 0.9;
            target_height = target_width / static_cast<double>(aspectratio);
        }
        return resize(static_cast<int>(target_width), static_cast<int>(target_height));
    }
}
