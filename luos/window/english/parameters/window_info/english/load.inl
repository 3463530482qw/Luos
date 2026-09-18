namespace Gnik_luos {
    Window_settings_info& Window_settings_info::batch_load(const simdjson::dom::element& json, std::string_view type) {
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

        if (!target_type.at_key("name").get_string().get(temporary_name)) {
            name = std::string(temporary_name);
        }
            
        if (!target_type.at_key("width").get_int64().get(temporary_width)) {
            width = static_cast<uint32_t>(temporary_width);
        }

        if (!target_type.at_key("height").get_int64().get(temporary_height)) {
            height = static_cast<uint32_t>(temporary_height);
        }
  
        if (!target_type.at_key("logic_width").get_int64().get(temporary_logic_width)) {
            logic_width = static_cast<uint32_t>(temporary_logic_width);
        }

        if (!target_type.at_key("logic_height").get_int64().get(temporary_logic_height)) {
            logic_height = static_cast<uint32_t>(temporary_logic_height);
        }
            
        if (!target_type.at_key("icon").get_string().get(temporary_icon)) {
            icon = std::string(temporary_icon);
        }
        
        if (!target_type.at_key("display_index").get_uint64().get(temporary_display_index)) {
            display_index = static_cast<uint8_t>(temporary_display_index);
        }

        if (!target_type.at_key("time").get_bool().get(temporary_is_time)) {
            is_time = temporary_is_time;
        }

        if (!target_type.at_key("key").get_bool().get(temporary_is_key)) {
            is_key = temporary_is_key;
        }

        if (!target_type.at_key("vulkan").get_bool().get(temporary_is_vulkan)) {
            is_vulkan = temporary_is_vulkan;
        }

        // 嵌在 window_info 里的两个子段:线条渲染的着色器名
        if (!target_type.at_key("line_render").get_object().at_key("vert").get_string().get(temporary_line_render_vert)) {
            line_render_vert = std::string(temporary_line_render_vert);
        }

        if (!target_type.at_key("line_render").get_object().at_key("frag").get_string().get(temporary_line_render_frag)) {
            line_render_frag = std::string(temporary_line_render_frag);
        }

        // 子段:清屏色
        if (!target_type.at_key("vulkan_clear_value").get_object().at_key("red").get_double().get(temporary_vulkan_clear_red)) {
            vulkan_clear_red = static_cast<float>(temporary_vulkan_clear_red);
        }

        if (!target_type.at_key("vulkan_clear_value").get_object().at_key("green").get_double().get(temporary_vulkan_clear_green)) {
            vulkan_clear_green = static_cast<float>(temporary_vulkan_clear_green);
        }

        if (!target_type.at_key("vulkan_clear_value").get_object().at_key("blue").get_double().get(temporary_vulkan_clear_blue)) {
            vulkan_clear_blue = static_cast<float>(temporary_vulkan_clear_blue);
        }

        if (!target_type.at_key("vulkan_clear_value").get_object().at_key("alpha").get_double().get(temporary_vulkan_clear_alpha)) {
            vulkan_clear_alpha = static_cast<float>(temporary_vulkan_clear_alpha);
        }

        return *this;
    }
}