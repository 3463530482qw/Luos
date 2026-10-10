namespace Gnik_luos {
    Information_image& Image::find(const std::string& path) {
        auto it = cache.find(path);
        if (it != cache.end()) {
            return it->second;   // 同一张图只解码一次
        }
        Information_image image;
        image.data = stbi_load(path.c_str(), &image.width, &image.height, nullptr, 4);
        if (!image.data) {
            throw std::runtime_error(std::string("Image::find => Image failed to load: ") + path + " (" + stbi_failure_reason() + ")");
        }
        return cache.emplace(path, image).first->second;
    }
}
