namespace Gnik_luos {
    Tilemap& Tilemap::texture(const std::string& path) {
        texture_key = path;
        texture_image = Information_image{};
        dirty = true;
        return *this;
    }

    Tilemap& Tilemap::texture(const Information_image& image) {   // 直接给已经加载好的像素:键用像素地址加宽高
        texture_image = image;
        texture_key.clear();
        if (image.data != nullptr) {
            texture_key = "image:" + std::to_string(reinterpret_cast<uintptr_t>(image.data))
                + ":" + std::to_string(image.width) + "x" + std::to_string(image.height);
        }
        dirty = true;
        return *this;
    }
}
