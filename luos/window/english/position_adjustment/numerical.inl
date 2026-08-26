namespace Gnik_luos {
    Window& Window::position_adjustment_numerical(int x, int y) {
        if(!SDL_SetWindowPosition(id, x, y)) {
            throw std::runtime_error(std::string("Window::position_adjustment_numerical => Position adjustment failed"));
        }
        return *this;
    }
    Window& Window::position_adjustment_numerical(float x, float y) {
        x = mode->w * x;
        y = mode->h * y;
        if(!SDL_SetWindowPosition(id, static_cast<int>(x), static_cast<int>(y))) {
            throw std::runtime_error(std::string("Window::position_adjustment_numerical => Position adjustment failed"));
        }
        return *this;
    }
}