namespace Gnik_luos {
    void Line::private_read_size(const simdjson::dom::element& source) {   // 缺键保默认:取不到的键不动成员
        simdjson::dom::object group{};
        if (source.get_object().get(group)) {
            return;
        }
        if (!group.at_key("width").get_double().get(temporary_x)) {
            size_x = static_cast<float>(temporary_x);
        }
        if (!group.at_key("height").get_double().get(temporary_x)) {
            size_y = static_cast<float>(temporary_x);
        }
    }
}
