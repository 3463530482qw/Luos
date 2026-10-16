namespace Gnik_luos {
    Text& Text::batch_load(const simdjson::dom::element& json, std::string_view type) {
        simdjson::dom::object root{};
        simdjson::dom::object body{};
        if (json.get_object().get(root) || root.at_key(type).get_object().get(body)) {
            throw std::runtime_error(
                std::string("text::batch_load: \"") +
                std::string(type) +
                std::string("\" Doesn't exist")
            );
        }

        face = nullptr;   // 字体要外面绑:json 里的键只是名字,这里没有字体仓库
        for (auto item : body) {
            if (item.key == "text") {
                read_text(item.value, content);
            } else if (item.key == "texture_path") {
                read_text(item.value, texture_key);   // 只对"没绑字体"那一档有意义
            } else if (item.key == "pos") {
                read_vector(item.value, x1, y1, z1);
            } else if (item.key == "font_size") {
                double value = 0.0;
                if (!item.value.get_double().get(value)) {
                    font_size = static_cast<float>(value);
                }
            } else if (item.key == "spacing") {
                read_size(item.value, letter_spacing, line_height);
            } else if (item.key == "align") {
                std::string value{};
                read_text(item.value, value);
                align_mode = read_align(value, align_mode);
            } else if (item.key == "rotation_point") {
                read_vector(item.value, rotation_point_x, rotation_point_y, rotation_point_z);
            } else if (item.key == "rotation") {
                read_vector(item.value, rotation_x, rotation_y, rotation_z);
            } else if (item.key == "rgba") {
                read_color(item.value, r, g, b, a);
            }
        }

        dirty = true;   // 参数换过一轮:下一轮 Draw::draw 重排顶点
        return *this;
    }
}
