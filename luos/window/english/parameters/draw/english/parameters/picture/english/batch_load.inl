namespace Gnik_luos {
    // 取 type 段当一张图读:data 给这张图的两个对角,第一个点是左上角;少一个点这张图不成立
    Picture& Picture::batch_load(const simdjson::dom::element& json, std::string_view type) {
        simdjson::dom::object root{};
        simdjson::dom::object body{};
        if (json.get_object().get(root) || root.at_key(type).get_object().get(body)) {
            throw std::runtime_error(
                std::string("picture::batch_load: \"") +
                std::string(type) +
                std::string("\" Doesn't exist")
            );
        }

        size_t corner = 0;
        Vector3 point{};
        for (auto item : body) {
            if (item.key == "data") {
                if (!item.value.is_array()) {
                    continue;   // 点表只收数组:类型不对当没写
                }
                for (auto entry : item.value.get_array()) {
                    if (!read_point(entry, point)) {
                        continue;   // 坏组丢掉
                    }
                    if (corner == 0) {
                        x1 = static_cast<float>(point.x);
                        y1 = static_cast<float>(point.y);
                        z1 = static_cast<float>(point.z);
                        ++corner;
                    } else if (corner == 1) {
                        x2 = static_cast<float>(point.x);
                        y2 = static_cast<float>(point.y);
                        z2 = static_cast<float>(point.z);
                        ++corner;   // 两个点就是这张图:多的不看
                    }
                }
            } else if (item.key == "rotation_point") {
                read_vector(item.value, rotation_point_x, rotation_point_y, rotation_point_z);
            } else if (item.key == "rotation") {
                read_vector(item.value, rotation_x, rotation_y, rotation_z);
            } else if (item.key == "rgba") {
                read_color_list(item.value, r, g, b, a, 4);
            } else if (item.key == "texture") {
                read_flag(item.value, use_texture);
            } else if (item.key == "texture_path") {
                read_text(item.value, texture_key);
                texture_image = Information_image{};
            }
        }

        private_ready = corner == 2;    // 两个角都落到数上才出顶点:库里不替它编宽高
        dirty = true;                   // 参数换过一轮:下一轮 Draw::draw 重算顶点
        return *this;
    }
}
