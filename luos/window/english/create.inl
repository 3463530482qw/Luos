namespace Gnik_luos {
    Window& Window::create(Window_create_info& Window_create_info) {
        id = SDL_CreateWindow(name.c_str(), width, height, Window_create_info.flage);
        if (!id) {
            throw std::runtime_error(std::string("Window::create => ") + SDL_GetError());
        }
        window_id = SDL_GetWindowID(id);
        anchor_to(Anchor_x::middle, Anchor_y::middle);   // 默认摆在屏幕正中
        return *this;
    }

    Window& Window::create() {
        Window_create_info Window_create_info;
        Window_create_info.private_load();
        return create(Window_create_info);
    }
}