namespace Gnik_luos {
    void Window::mouse_update(float mouse_x, float mouse_y) {
        mouse.x = std::clamp((mouse_x - static_cast<float>(cut_offset_width)) / re_aspectratio, 0.0f, static_cast<float>(logic_width));
        mouse.y = std::clamp((mouse_y - static_cast<float>(cut_offset_height)) / re_aspectratio, 0.0f, static_cast<float>(logic_height));
    }
}