namespace Gnik_luos {
    Window& Window::position_adjustment_positional(int x, int y) {
        if (x == 1) {
            x = 0;
            if (y == 1) {
                y = 0;
            } else if (y == 2) {
                y = (mode->h - height) * 0.5f;
            } else {
                y = (mode->h - height);
            }
        } else if (x == 2) {
            x = (mode->w - width) * 0.5f;
            if (y == 1) {
                y = 0;
            } else if (y == 2) {
                y = (mode->h - height) * 0.5f;
            } else {
                y = (mode->h - height);
            }
        } else {
            x = (mode->w - width);
            if (y == 1) {
                y = 0;
            } else if (y == 2) {
                y = (mode->h - height) * 0.5f;
            } else {
                y = (mode->h - height);
            }
        }
        if(!SDL_SetWindowPosition(id, x, y)) {
            throw std::runtime_error(std::string("Window::position_adjustment_positional => Position adjustment failed"));
        }
        return *this;
    }
}