namespace Gnik_luos {
    Line& Line::batch_load(const simdjson::dom::element& json, std::string_view type) {   // 取 type 段当一条线读:段内 to 有几组(重复键或多组值)就有几段
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
            if (item.key == "from") {
                if (private_read_point(item.value, point)) {
                    x1 = static_cast<float>(point.x);
                    y1 = static_cast<float>(point.y);
                    z1 = static_cast<float>(point.z);
                }
            } else if (item.key == "to") {
                if (!item.value.is_array()) {
                    if (private_read_point(item.value, point)) {
                        to_point.push_back(point);
                    }
                    continue;
                }
                for (auto entry : item.value.get_array()) {
                    if (private_read_point(entry, point)) {
                        to_point.push_back(point);
                    }
                }
            } else if (item.key == "size") {
                private_read_size(item.value);
            } else if (item.key == "rotation_point") {
                private_read_rotation_point(item.value);
            } else if (item.key == "rotation") {
                private_read_rotation(item.value);
            } else if (item.key == "rgba") {
                private_read_rgba(item.value);
            }
        }

        dirty = true;   // 参数换过一轮:下一轮 Draw::draw 重算顶点
        return *this;
    }
}
