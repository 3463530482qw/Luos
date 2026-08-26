namespace Gnik_luos {
    Window& Window::create(Window_create_info& Window_create_info) {
        id = SDL_CreateWindow(name.c_str(), width, height, Window_create_info.flage);
        if (!id) {
            throw std::runtime_error(std::string("Window::create => ") + SDL_GetError());
        }
        wid = SDL_GetWindowID(id);
        position_adjustment_positional(window_position::middle, window_position::middle);
        return *this;
    }

    Window& Window::create() {
        Window_create_info Window_create_info;
        Window_create_info.private_load();
        return create(Window_create_info);
    }
}