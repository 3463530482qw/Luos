namespace Gnik_luos {
    Line& Line::texture(bool value) {
        use_texture = value;
        if (!value) {
            texture_key.clear();
            texture_image = Information_image{};
        }
        dirty = true;
        return *this;
    }

    Line& Line::texture(const std::string& path) {
        texture_key = path;
        texture_image = Information_image{};
        use_texture = true;
        dirty = true;
        return *this;
    }

    Line& Line::texture(const Information_image& image) {   // 直接拿已经加载好的像素当贴图:槽位键用像素地址
        texture_image = image;
        texture_key = image.data == nullptr ? std::string{} : "image:" + std::to_string(reinterpret_cast<uintptr_t>(image.data));
        use_texture = true;
        dirty = true;
        return *this;
    }
}
