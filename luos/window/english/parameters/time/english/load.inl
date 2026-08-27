namespace Gnik_luos {
    Window_time& Window_time::load() {
        set_fps = 0.01666;
        youk_smooth = true;
        return *this;
    }
    Window_time& Window_time::batch_load(const simdjson::dom::element& json, std::string_view type) {
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

        if (!target_type.at_key("fps").get_double().get(temporary_set_fps)) {
            set_fps = 1.0f / temporary_set_fps;
        }
        if (!target_type.at_key("youk_smooth").get_bool().get(temporary_youk_smooth)) {
            youk_smooth = temporary_youk_smooth;
        }
        return *this;
    }
}