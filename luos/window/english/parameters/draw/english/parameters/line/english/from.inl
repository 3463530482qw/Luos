namespace Gnik_luos {
    Line& Line::from(float x, float y, float z) {
        x1 = x;
        y1 = y;
        z1 = z;
        dirty = true;
        return *this;
    }
}
