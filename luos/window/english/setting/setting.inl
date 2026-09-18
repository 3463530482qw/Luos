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
        is_time = window_settings_info.is_time;
        is_key = window_settings_info.is_key;
        is_vulkan = window_settings_info.is_vulkan;

        // 线条渲染的着色器名与清屏色(窗口配置信息里那两个子段),交给 window_vulkan 用
        window_vulkan.line_render.vertex_shader_file = window_settings_info.line_render_vert;
        window_vulkan.line_render.fragment_shader_file = window_settings_info.line_render_frag;
        window_vulkan.renderpass.clear_value = vk::ClearValue{vk::ClearColorValue{std::array{
            window_settings_info.vulkan_clear_red,
            window_settings_info.vulkan_clear_green,
            window_settings_info.vulkan_clear_blue,
            window_settings_info.vulkan_clear_alpha
        }}};
        return *this;
    }
    Window& Window::setting() {
        Window_settings_info window_settings_info;
        setting(window_settings_info);
        return *this;
    }
}
