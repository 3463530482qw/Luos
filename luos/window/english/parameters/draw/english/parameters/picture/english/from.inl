namespace Gnik_luos {
    Picture& Picture::from(float x, float y, float z) {
        x1 = x;
        y1 = y;
        z1 = z;
        dirty = true;
        return *this;
    }
}
