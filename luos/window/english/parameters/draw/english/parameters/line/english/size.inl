namespace Gnik_luos {
    Line& Line::size(float x_value, float y_value) {
        size_x = x_value;
        size_y = y_value;
        dirty = true;
        return *this;
    }
}
