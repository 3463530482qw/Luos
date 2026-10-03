namespace Gnik_luos {
    Line& Line::to(float x, float y, float z) {
        x2 = x;
        y2 = y;
        z2 = z;
        dirty = true;
        return *this;
    }
}
