namespace Gnik_luos {
    Line& Line::rotation_point(float x, float y, float z) {
        rotation_point_x = x;
        rotation_point_y = y;
        rotation_point_z = z;
        dirty = true;
        return *this;
    }
}
