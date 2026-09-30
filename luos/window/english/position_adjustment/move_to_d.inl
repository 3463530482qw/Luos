namespace Gnik_luos {
    // 按显示器尺寸的比例摆位:0~1 是比例,越界由调用方自己保证
    Window& Window::move_to(double x, double y) {
        const int target_x = static_cast<int>(static_cast<double>(mode->w) * x);
        const int target_y = static_cast<int>(static_cast<double>(mode->h) * y);
        return move_to(target_x, target_y);
    }
}
