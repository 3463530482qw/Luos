namespace Gnik_luos {
    Window_create_info& Window_create_info::batch_load(const simdjson::dom::element& json, std::string_view type) {
        if (json.get_object().get(json_object)) {
            throw std::runtime_error("windowinfo::batch_load: JSON load failed");
        }

        if (json_object.at_key(type.data()).get(config) || !config.is_object()) {
            throw std::runtime_error(
                std::string("windowinfo::batch_load: \"") + 
                type.data() + 
                std::string("\" Doesn't exist")
            );
        }
        target_type = config.get_object();

        if (!target_type.at_key("fullscreen").get_bool().get(temporary_fullscreen)) {
            fullscreen = temporary_fullscreen;
        }
        if (!target_type.at_key("occluded").get_bool().get(temporary_occluded)) {
            occluded = temporary_occluded;
        }
        if (!target_type.at_key("hidden").get_bool().get(temporary_hidden)) {
            hidden = temporary_hidden;
        }
        if (!target_type.at_key("borderless").get_bool().get(temporary_borderless)) {
            borderless = temporary_borderless;
        }
        if (!target_type.at_key("resizable").get_bool().get(temporary_resizable)) {
            resizable = temporary_resizable;
        }
        if (!target_type.at_key("minimized").get_bool().get(temporary_minimized)) {
            minimized = temporary_minimized;
        }
        if (!target_type.at_key("maximized").get_bool().get(temporary_maximized)) {
            maximized = temporary_maximized;
        }
        if (!target_type.at_key("mouse_grabbed").get_bool().get(temporary_mouse_grabbed)) {
            mouse_grabbed = temporary_mouse_grabbed;
        }
        if (!target_type.at_key("input_focus").get_bool().get(temporary_input_focus)) {
            input_focus = temporary_input_focus;
        }
        if (!target_type.at_key("mouse_focus").get_bool().get(temporary_mouse_focus)) {
            mouse_focus = temporary_mouse_focus;
        }
        if (!target_type.at_key("external").get_bool().get(temporary_external)) {
            external = temporary_external;
        }
        if (!target_type.at_key("modal").get_bool().get(temporary_modal)) {
            modal = temporary_modal;
        }
        if (!target_type.at_key("high_pixel_density").get_bool().get(temporary_high_pixel_density)) {
            high_pixel_density = temporary_high_pixel_density;
        }
        if (!target_type.at_key("mouse_capture").get_bool().get(temporary_mouse_capture)) {
            mouse_capture = temporary_mouse_capture;
        }
        if (!target_type.at_key("mouse_relative_mode").get_bool().get(temporary_mouse_relative_mode)) {
            mouse_relative_mode = temporary_mouse_relative_mode;
        }
        if (!target_type.at_key("always_on_top").get_bool().get(temporary_always_on_top)) {
            always_on_top = temporary_always_on_top;
        }
        if (!target_type.at_key("utility").get_bool().get(temporary_utility)) {
            utility = temporary_utility;
        }
        if (!target_type.at_key("tooltip").get_bool().get(temporary_tooltip)) {
            tooltip = temporary_tooltip;
        }
        if (!target_type.at_key("popup_menu").get_bool().get(temporary_popup_menu)) {
            popup_menu = temporary_popup_menu;
        }
        if (!target_type.at_key("keyboard_grabbed").get_bool().get(temporary_keyboard_grabbed)) {
            keyboard_grabbed = temporary_keyboard_grabbed;
        }
        if (!target_type.at_key("fill_document").get_bool().get(temporary_fill_document)) {
            fill_document = temporary_fill_document;
        }
        if (!target_type.at_key("transparent").get_bool().get(temporary_transparent)) {
            transparent = temporary_transparent;
        }
        if (!target_type.at_key("not_focusable").get_bool().get(temporary_not_focusable)) {
            not_focusable = temporary_not_focusable;
        }
        if (!target_type.at_key("opengl").get_bool().get(temporary_opengl)) {
            opengl = temporary_opengl;
        }
        if (!target_type.at_key("vulkan").get_bool().get(temporary_vulkan)) {
            vulkan = temporary_vulkan;
        }
        if (!target_type.at_key("metal").get_bool().get(temporary_metal)) {
            metal = temporary_metal;
        }
        private_load();
        return *this;
    }
}