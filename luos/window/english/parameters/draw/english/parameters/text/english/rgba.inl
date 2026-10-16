namespace Gnik_luos {
    Text& Text::rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha) {
        r = red;
        g = green;
        b = blue;
        a = alpha;
        dirty = true;
        return *this;
    }
}
