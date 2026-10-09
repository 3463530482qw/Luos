namespace Gnik_luos {
    void Line::private_read_rgba(const simdjson::dom::element& source) {   // 缺键保默认:取不到的键不动成员
        simdjson::dom::object group{};
        if (source.get_object().get(group)) {
            return;
        }
        if (!group.at_key("red").get_int64().get(temporary_color)) {
            r = static_cast<uint8_t>(temporary_color);
        }
        if (!group.at_key("green").get_int64().get(temporary_color)) {
            g = static_cast<uint8_t>(temporary_color);
        }
        if (!group.at_key("blue").get_int64().get(temporary_color)) {
            b = static_cast<uint8_t>(temporary_color);
        }
        if (!group.at_key("alpha").get_double().get(temporary_x)) {
            a = static_cast<float>(temporary_x);
        }
    }
}
