namespace Gnik_luos {
    bool Line::private_read_point(const simdjson::dom::element& source, Vector3& target) {   // 读一组 {x,y,z}:缺任何一个分量这组就不成立
        if (source.get_object().at_key("x").get_double().get(temporary_x)) {
            return false;
        }
        if (source.get_object().at_key("y").get_double().get(temporary_y)) {
            return false;
        }
        if (source.get_object().at_key("z").get_double().get(temporary_z)) {
            return false;
        }
        target = Vector3{temporary_x, temporary_y, temporary_z};
        return true;
    }
}
