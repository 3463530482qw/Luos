namespace Gnik_luos {
    Picture& Picture::texture(bool value) {
        use_texture = value;
        if (!value) {
            texture_key.clear();
            texture_image = Information_image{};
        }
        dirty = true;
        return *this;
    }

    Picture& Picture::texture(const std::string& path) {
        texture_key = path;
        texture_image = Information_image{};
        use_texture = true;
        dirty = true;
        return *this;
    }

    Picture& Picture::texture(const Information_image& image) {   // 直接拿已经加载好的像素当贴图:键用像素地址加宽高
        texture_image = image;
        texture_key.clear();
        if (image.data != nullptr) {
            texture_key = "image:" + std::to_string(reinterpret_cast<uintptr_t>(image.data))
                + ":" + std::to_string(image.width) + "x" + std::to_string(image.height);
        }
        use_texture = true;
        dirty = true;
        return *this;
    }
}
