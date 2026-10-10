namespace Gnik_luos {
    Line& Line::texture(bool value) {
        use_texture = value;
        dirty = true;
        return *this;
    }
}
