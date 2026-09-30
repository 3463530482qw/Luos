namespace Gnik_luos {
    // 按配置算窗口尺寸:配置里没给就按当前显示器的 90% 摆一个 16:9 的窗口。
    // 顺带把画布比例算定(画布比例不随窗口变化,视口靠它取内接矩形)
    void Window::apply_window_size(const Window_settings_info& window_settings_info) {
        if (window_settings_info.width == 0 && window_settings_info.height == 0) {
            double target_width{};
            double target_height{};
            if ((static_cast<double>(mode->w) / static_cast<double>(mode->h) > 1.7778)) {
                target_height = static_cast<double>(mode->h) * 0.9;
                target_width = target_height * 1.7778;
            } else {
                target_width = static_cast<double>(mode->w) * 0.9;
                target_height = target_width / 1.7778;
            }
            width = static_cast<uint32_t>(target_width);
            height = static_cast<uint32_t>(target_height);
        } else {
            width = window_settings_info.width;
            height = window_settings_info.height;
        }
        aspectratio = static_cast<float>(width) / static_cast<float>(height);
        logic_width = window_settings_info.logic_width;
        logic_height = window_settings_info.logic_height;
    }
}
