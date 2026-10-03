namespace Gnik_luos {
    Line& Line::width(float value) {
        thickness = value;
        dirty = true;
        return *this;
    }
}
