namespace Gnik_luos {
    bool read_point(const simdjson::dom::element& source, Vector3& target) {   // 读一组 {x,y,z}:缺任何一个分量这组就不成立
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        if (source.get_object().at_key("x").get_double().get(x)) {
            return false;
        }
        if (source.get_object().at_key("y").get_double().get(y)) {
            return false;
        }
        if (source.get_object().at_key("z").get_double().get(z)) {
            return false;
        }
        target = Vector3{x, y, z};
        return true;
    }
}
