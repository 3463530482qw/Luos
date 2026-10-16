namespace Gnik_luos {
    void read_size(const simdjson::dom::element& source, float& width, float& height) {   // 缺键保默认:取不到的键不动目标
        simdjson::dom::object group{};
        if (source.get_object().get(group)) {
            return;
        }
        double value = 0.0;
        if (!group.at_key("width").get_double().get(value)) {
            width = static_cast<float>(value);
        }
        if (!group.at_key("height").get_double().get(value)) {
            height = static_cast<float>(value);
        }
    }
}
