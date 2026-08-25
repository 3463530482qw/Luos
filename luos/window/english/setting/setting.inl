namespace Gnik_luos {
    Window& Window::setting(Window_settings_info window_settings_info) {
        if (displays.empty()) {
            int count = 0;
            SDL_DisplayID* ids = SDL_GetDisplays(&count);
            displays.assign(ids, ids + count);
            SDL_free(ids);
        }
        display_index = (window_settings_info.display_index < displays.size()) ? window_settings_info.display_index : 0;
        mode = SDL_GetCurrentDisplayMode(displays[display_index]);
        #include "width_and_height.inl"
        name = window_settings_info.name;
        icon = window_settings_info.icon;
        return *this;
    }
    Window& Window::setting() {
        Window_settings_info window_settings_info;
        setting(window_settings_info);
        return *this;
    }
}