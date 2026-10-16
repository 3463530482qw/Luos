namespace Gnik_luos {
    void read_vector(const simdjson::dom::element& source, float& x, float& y, float& z) {   // 读一组 {x,y,z}(旋转与旋转点共用);缺键保默认
        simdjson::dom::object group{};
        if (source.get_object().get(group)) {
            return;
        }
        double value = 0.0;
        if (!group.at_key("x").get_double().get(value)) {
            x = static_cast<float>(value);
        }
        if (!group.at_key("y").get_double().get(value)) {
            y = static_cast<float>(value);
        }
        if (!group.at_key("z").get_double().get(value)) {
            z = static_cast<float>(value);
        }
    }
}
