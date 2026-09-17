namespace Gnik_luos {
    Window& Window::resize() {
        // 窗口尺寸按画布比例取显示器 90%:asymptratio 是画布比例,不是窗口当前比例
        float target_width{}, target_height{};
        if ((static_cast<float>(mode->w) / static_cast<float>(mode->h) > aspectratio)) {
            target_height = mode->h * 0.9f;
            target_width = target_height * aspectratio;
        } else {
            target_width = mode->w * 0.9f;
            target_height = target_width / aspectratio;
        }
        return resize(static_cast<int>(target_width), static_cast<int>(target_height));
    }

    Window& Window::resize(int w, int h) {
        if(!SDL_SetWindowSize(id, w, h)) {
            throw std::runtime_error(std::string("Window::resize => Window resize failed: ") + SDL_GetError());
        }
        width = w;
        height = h;
        // 窗口比例变了也不改 aspectratio:视口仍按画布比例取内接矩形,余量留灰边
        window_vulkan.viewport.rebuild();
        window_vulkan.request_rebuild(width, height, aspectratio);
        return *this;
    }

    Window& Window::resize(float w, float h) {
        return resize(static_cast<int>(mode->w * w), static_cast<int>(mode->h * h));
    }
}
