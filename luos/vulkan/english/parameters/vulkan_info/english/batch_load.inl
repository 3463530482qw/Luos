namespace Gnik_luos {
    Vulkan_info& Vulkan_info::batch_load(const simdjson::dom::element& json, std::string_view type) {
        if (json.get_object().get(json_object)) {
            throw std::runtime_error("vulkaninfo::batch_load: JSON load failed");
        }

        if (json_object.at_key(type.data()).get(config) || !config.is_object()) {
            throw std::runtime_error(
                std::string("vulkaninfo::batch_load: \"") +
                type.data() +
                std::string("\" Doesn't exist")
            );
        }
        target_type = config.get_object();

        if (!target_type.at_key("window_name").get_string().get(temporary_window_name)) {
            window_name = std::string(temporary_window_name);
        }

        // 地面:整个子段缺了也不抛,保持默认(与 window_info 里 line_render 那段同一口径)
        if (!target_type.at_key("ground").get_object().at_key("enabled").get_bool().get(temporary_ground)) {
            ground = temporary_ground;
        }

        if (!target_type.at_key("ground").get_object().at_key("grid_size").get_double().get(temporary_ground_grid_size)) {
            ground_grid_size = static_cast<float>(temporary_ground_grid_size);
        }

        if (!target_type.at_key("ground").get_object().at_key("major_every").get_double().get(temporary_ground_major_every)) {
            ground_major_every = static_cast<float>(temporary_ground_major_every);
        }

        if (!target_type.at_key("ground").get_object().at_key("fade_distance").get_double().get(temporary_ground_fade_distance)) {
            ground_fade_distance = static_cast<float>(temporary_ground_fade_distance);
        }

        if (!target_type.at_key("ground").get_object().at_key("minor").get_object().at_key("red").get_double().get(temporary_ground_minor_red)) {
            ground_minor_red = static_cast<float>(temporary_ground_minor_red);
        }

        if (!target_type.at_key("ground").get_object().at_key("minor").get_object().at_key("green").get_double().get(temporary_ground_minor_green)) {
            ground_minor_green = static_cast<float>(temporary_ground_minor_green);
        }

        if (!target_type.at_key("ground").get_object().at_key("minor").get_object().at_key("blue").get_double().get(temporary_ground_minor_blue)) {
            ground_minor_blue = static_cast<float>(temporary_ground_minor_blue);
        }

        if (!target_type.at_key("ground").get_object().at_key("minor").get_object().at_key("alpha").get_double().get(temporary_ground_minor_alpha)) {
            ground_minor_alpha = static_cast<float>(temporary_ground_minor_alpha);
        }

        if (!target_type.at_key("ground").get_object().at_key("major").get_object().at_key("red").get_double().get(temporary_ground_major_red)) {
            ground_major_red = static_cast<float>(temporary_ground_major_red);
        }

        if (!target_type.at_key("ground").get_object().at_key("major").get_object().at_key("green").get_double().get(temporary_ground_major_green)) {
            ground_major_green = static_cast<float>(temporary_ground_major_green);
        }

        if (!target_type.at_key("ground").get_object().at_key("major").get_object().at_key("blue").get_double().get(temporary_ground_major_blue)) {
            ground_major_blue = static_cast<float>(temporary_ground_major_blue);
        }

        if (!target_type.at_key("ground").get_object().at_key("major").get_object().at_key("alpha").get_double().get(temporary_ground_major_alpha)) {
            ground_major_alpha = static_cast<float>(temporary_ground_major_alpha);
        }

        if (!target_type.at_key("ground").get_object().at_key("vert").get_string().get(temporary_ground_vert)) {
            ground_vert = std::string(temporary_ground_vert);
        }

        if (!target_type.at_key("ground").get_object().at_key("frag").get_string().get(temporary_ground_frag)) {
            ground_frag = std::string(temporary_ground_frag);
        }

        return *this;
    }
}
