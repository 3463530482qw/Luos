namespace Gnik_luos {
    void Line::private_read_rotation_point(const simdjson::dom::element& source) {   // 缺键保默认:取不到的键不动成员
        simdjson::dom::object group{};
        if (source.get_object().get(group)) {
            return;
        }
        if (!group.at_key("x").get_double().get(temporary_x)) {
            rotation_point_x = static_cast<float>(temporary_x);
        }
        if (!group.at_key("y").get_double().get(temporary_x)) {
            rotation_point_y = static_cast<float>(temporary_x);
        }
        if (!group.at_key("z").get_double().get(temporary_x)) {
            rotation_point_z = static_cast<float>(temporary_x);
        }
    }
}
