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
        apply_window_size(window_settings_info);
        name = window_settings_info.name;
        icon = window_settings_info.icon;
        is_time = window_settings_info.is_time;
        is_key = window_settings_info.is_key;
        is_vulkan = window_settings_info.is_vulkan;

        // 画布尺寸随配置走:取景范围与视口都跟着新的画布口径重算(实体与绑定在构造期已定)
        camera.canvas_width = static_cast<double>(logic_width);
        camera.canvas_height = static_cast<double>(logic_height);
        // 相机子模块的初始取景:window_info 里写了 camera 段就用它,没写就保持默认(正交、位置 (0,0,0))
        camera.apply(window_settings_info);
        window_vulkan.update_viewport();

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

    // 定义放窗口模块:这里 Camera 与 Window_settings_info 都完整(相机模块不该反向依赖窗口配置)
    Camera& Camera::apply(const Window_settings_info& settings) {
        if (!settings.has_camera) {
            return *this;   // 没写 camera 段:保持默认取景
        }
        is_perspective = settings.camera_is_perspective;
        position.position.x = settings.camera_x;
        position.position.y = settings.camera_y;
        position.position.z = settings.camera_z;
        rotation_x = settings.camera_rotation_x;
        rotation_y = settings.camera_rotation_y;
        rotation_z = settings.camera_rotation_z;
        fov = settings.camera_fov;
        near_plane = settings.camera_near_plane;
        far_plane = settings.camera_far_plane;
        zoom = settings.camera_zoom;
        return *this;
    }
}
