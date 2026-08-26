namespace Gnik_luos {
    Window& Window::resize() {
        float target_width{}, target_height{};
        if ((static_cast<float>(mode->w) / static_cast<float>(mode->h) > aspectratio)) {
            target_height = mode->h * 0.9f;
            target_width = target_height * aspectratio;
        } else {
            target_width = mode->w * 0.9f;
            target_height = target_width / aspectratio;
        }
        width = static_cast<int>(target_width);
        height = static_cast<int>(target_height);
        if(!SDL_SetWindowSize(id, width, height)) {
            throw std::runtime_error(std::string("Window::resize => Window resize failed"));
        }
        return *this;
    }
    Window& Window::resize(int w, int h) {
        aspectratio = static_cast<float>(w) / static_cast<float>(h);
        if(!SDL_SetWindowSize(id, w, h)) {
            throw std::runtime_error(std::string("Window::resize => Window resize failed"));
        }
        return *this;
    }

    Window& Window::resize(float w, float h) {
        w = mode->w * w;
        h = mode->h * h;
        aspectratio = w / h;
        if(!SDL_SetWindowSize(id, w, h)) {
            throw std::runtime_error(std::string("Window::resize => Window resize failed"));
        }
        return *this;
    }
}