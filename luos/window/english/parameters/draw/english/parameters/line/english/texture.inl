namespace Gnik_luos {
    Line& Line::texture(bool value) {
        use_texture = value;
        if (!value) {
            texture_path.clear();
        }
        dirty = true;
        return *this;
    }

    Line& Line::texture(const std::string& path) {
        texture_path = path;
        use_texture = true;
        dirty = true;
        return *this;
    }
}
