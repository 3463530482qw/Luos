namespace Gnik_luos {
    Image& Image::load(const char* path) {
        Information_image& image = find(std::string(path));   // 解码归缓存管,同一路径只解一次
        pack.emplace_back();
        pack.back().push_back(image);
        return *this;
    }
    Image& Image::batch_load(const simdjson::dom::element& json, std::string_view type) {
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

        pack.emplace_back();

        for (auto field : config.get_object()) {
            if (field.value.get_string().get(temporary_path)) {
                throw std::runtime_error(
                    std::string("Scene::batch_load => batch_load: path for \"") + 
                    field.key.data() + 
                    std::string("\" is not a string")
                );
                continue;
            }
            pack.back().push_back(find(std::string(temporary_path)));   // 解码与去重归缓存:同一路径只有一份像素,换图不会每次都换地址
        }
        return *this;
    }
}