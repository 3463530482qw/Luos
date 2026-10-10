namespace Gnik_luos {
    Image& Image::clear() {
        for (auto& entry : cache) {
            if (entry.second.data) {
                stbi_image_free(entry.second.data);
                entry.second.data = nullptr;
            }
        }
        cache.clear();   // 像素只归缓存所有,pack 里拿的是共享同一块 data 的浅拷贝
        pack.clear();
        return *this;
    }
}
