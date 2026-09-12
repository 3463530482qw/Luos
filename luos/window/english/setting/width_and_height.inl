if (window_settings_info.width == 0 && window_settings_info.height == 0) {
    float target_width{}, target_height{};
    if ((static_cast<float>(mode->w) / static_cast<float>(mode->h) > 1.7778f)) {
        target_height = mode->h * 0.9f;
        target_width = target_height * 1.7778f;
    } else {
        target_width = mode->w * 0.9f;
        target_height = target_width / 1.7778f;
    }
    width = target_width;
    height = target_height;
} else {
    width = window_settings_info.width;
    height = window_settings_info.height;
}
aspectratio = static_cast<float>(width) / static_cast<float>(height);
logic_width = window_settings_info.logic_width;
logic_height = window_settings_info.logic_height;