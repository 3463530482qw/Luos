namespace Gnik_luos {
    // 屏幕上的绝对尺寸:不按比例折算,直接给像素
    Window& Window::resize(int w, int h) {
        if (!SDL_SetWindowSize(id, w, h)) {
            throw std::runtime_error(std::string("Window::resize => Window resize failed: ") + SDL_GetError());
        }
        width = static_cast<uint32_t>(w);
        height = static_cast<uint32_t>(h);
        window_resize(static_cast<float>(width), static_cast<float>(height));
        return *this;
    }
}
