namespace Gnik_luos {
    Text& Text::rotation_point(float x, float y, float z) {
        rotation_point_x = x;
        rotation_point_y = y;
        rotation_point_z = z;
        dirty = true;
        return *this;
    }

    Text& Text::rotation(float x, float y, float z) {
        rotation_x = x;
        rotation_y = y;
        rotation_z = z;
        dirty = true;
        return *this;
    }
}
