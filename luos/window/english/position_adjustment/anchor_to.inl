namespace Gnik_luos {
    // 贴到屏幕的某个角/中点:枚举值就是份数,2 份代表整段,所以直接用 it / 2 换算
    // 垂直按 y 向下的屏幕口径:上 = 0、下 = 整段
    Window& Window::anchor_to(Anchor_x anchor_x, Anchor_y anchor_y) {
        const double x = static_cast<double>(static_cast<int>(anchor_x)) / 2.0 * static_cast<double>(mode->w - width);
        const double y = static_cast<double>(static_cast<int>(anchor_y)) / 2.0 * static_cast<double>(mode->h - height);
        return move_to(static_cast<int>(x), static_cast<int>(y));
    }
}
