namespace Gnik_luos {
    Image& load(const char* path) {
        Information_image image;
        image.data = stbi_load(path, &image.width, &image.height, nullptr, 4);
        if (!image.data) {
            throw std::runtime_error(std::string("Image::load => Image failed to load: ") + path + " (" + stbi_failure_reason() + ")");
        }
        pack.emplace_back();
        pack.back().push_back(image);
        return *this;
    }
    Image& batch_load(const simdjson::dom::element& json, std::string_view type) {
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

        if (!target_type.at_key("fps").get_string().get(temporary_set_fps)) {
            set_fps = 1.0f / temporary_set_fps;
        }
    }
}