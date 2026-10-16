namespace Gnik_luos {
    Picture& Picture::rotation(float x, float y, float z) {
        rotation_x = x;
        rotation_y = y;
        rotation_z = z;
        dirty = true;
        return *this;
    }
}
