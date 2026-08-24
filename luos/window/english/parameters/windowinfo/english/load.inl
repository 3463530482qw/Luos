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
            width = static_cast<int>(temporary_width);
        }

        if (!target_type.at_key("height").get_int64().get(temporary_height)) {
            height = static_cast<int>(temporary_height);
        }
  
        if (!target_type.at_key("logic_width").get_int64().get(temporary_logic_width)) {
            logic_width = static_cast<int>(temporary_logic_width);
        }

        if (!target_type.at_key("logic_height").get_int64().get(temporary_logic_height)) {
            logic_height = static_cast<int>(temporary_logic_height);
        }
            
        if (!target_type.at_key("icon").get_string().get(temporary_icon)) {
            icon = std::string(temporary_icon);
        }
        
        if (!target_type.at_key("display_index").get_uint64().get(temporary_display_index)) {
            display_index = static_cast<uint8_t>(temporary_display_index);
        }
            
        return *this;
    }
}