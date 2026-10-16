namespace Gnik_luos {
    Text& Text::font(Font& face_value) {
        face = &face_value;
        dirty = true;
        return *this;
    }

    Text& Text::from(float x, float y, float z) {
        x1 = x;
        y1 = y;
        z1 = z;
        dirty = true;
        return *this;
    }

    Text& Text::texture(const std::string& path) {
        texture_key = path;   // 只对"没绑字体"那一档有意义:绑了字体时图集就是贴图
        dirty = true;
        return *this;
    }

    Text& Text::text(const std::string& value) {
        content = value;
        dirty = true;
        return *this;
    }
}
