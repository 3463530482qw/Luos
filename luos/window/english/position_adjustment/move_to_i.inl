namespace Gnik_luos {
    // 屏幕上的绝对位置:不去管当前显示器与窗口尺寸,直接放到指定像素
    Window& Window::move_to(int x, int y) {
        if (!SDL_SetWindowPosition(id, x, y)) {
            throw std::runtime_error(std::string("Window::move_to => Position adjustment failed"));
        }
        return *this;
    }
}
