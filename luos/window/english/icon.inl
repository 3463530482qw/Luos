namespace Gnik_luos {
    Window& Window::set_icon(Information_image image) {
        SDL_Surface* surf = SDL_CreateSurface(image.width, image.height, SDL_PIXELFORMAT_RGBA32);
        if (!surf) {
            throw std::runtime_error(std::string("Window::set_icon => Failed to create surface: ") + std::string(SDL_GetError()));
        }
        memcpy(surf->pixels, image.data, image.width * image.height * 4);
        pre_event_ptr.type = 0x8000;
        pre_event_ptr.user.code = 1;
        pre_event_ptr.user.data1 = surf;
        pre_event_ptr.user.windowID = window_id;
        SDL_PushEvent(&pre_event_ptr);
        return *this;
    }
}