namespace Gnik_luos {
    // 按显示器尺寸的比例改窗口大小(0~1)
    Window& Window::resize(float w, float h) {
        const int target_width = static_cast<int>(static_cast<double>(mode->w) * w);
        const int target_height = static_cast<int>(static_cast<double>(mode->h) * h);
        return resize(target_width, target_height);
    }
}
