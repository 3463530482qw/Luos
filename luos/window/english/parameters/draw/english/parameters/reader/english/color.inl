namespace Gnik_luos {
    void read_color(const simdjson::dom::element& source, uint8_t& red, uint8_t& green, uint8_t& blue, float& alpha) {   // 缺键保默认
        simdjson::dom::object group{};
        if (source.get_object().get(group)) {
            return;
        }
        int64_t color = 0;
        double value = 0.0;
        if (!group.at_key("red").get_int64().get(color)) {
            red = static_cast<uint8_t>(color);
        }
        if (!group.at_key("green").get_int64().get(color)) {
            green = static_cast<uint8_t>(color);
        }
        if (!group.at_key("blue").get_int64().get(color)) {
            blue = static_cast<uint8_t>(color);
        }
        if (!group.at_key("alpha").get_double().get(value)) {
            alpha = static_cast<float>(value);
        }
    }
}
