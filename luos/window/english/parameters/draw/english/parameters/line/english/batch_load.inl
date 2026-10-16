namespace Gnik_luos {
    Line& Line::batch_load(const simdjson::dom::element& json, std::string_view type) {   // 取 type 段当一条线读:data 是点表,首点起点、其余顺次连成折线
        simdjson::dom::object root{};
        simdjson::dom::object body{};
        if (json.get_object().get(root) || root.at_key(type).get_object().get(body)) {
            throw std::runtime_error(
                std::string("line::batch_load: \"") +
                std::string(type) +
                std::string("\" Doesn't exist")
            );
        }

        to_point.clear();
        Vector3 point{};
        for (auto item : body) {
            if (item.key == "data") {
                if (!item.value.is_array()) {
                    continue;   // 点表只收数组:类型不对当没写
                }
                bool head = true;
                for (auto entry : item.value.get_array()) {
                    if (!read_point(entry, point)) {
                        continue;   // 坏组丢掉,其余照旧
                    }
                    if (head) {
                        x1 = static_cast<float>(point.x);
                        y1 = static_cast<float>(point.y);
                        z1 = static_cast<float>(point.z);
                        head = false;
                        continue;
                    }
                    to_point.push_back(point);
                }
            } else if (item.key == "size") {
                read_size(item.value, size_x, size_y);
            } else if (item.key == "rotation_point") {
                read_vector(item.value, rotation_point_x, rotation_point_y, rotation_point_z);
            } else if (item.key == "rotation") {
                read_vector(item.value, rotation_x, rotation_y, rotation_z);
            } else if (item.key == "rgba") {
                read_color(item.value, r, g, b, a);
            } else if (item.key == "texture") {
                read_flag(item.value, use_texture);
            } else if (item.key == "texture_path") {
                read_text(item.value, texture_key);
                texture_image = Information_image{};
            } else if (item.key == "seal") {
                read_flag(item.value, use_seal);
            }
        }

        dirty = true;   // 参数换过一轮:下一轮 Draw::draw 重算顶点
        return *this;
    }
}
