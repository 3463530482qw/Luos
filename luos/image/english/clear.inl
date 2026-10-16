namespace Gnik_luos {
    Image& Image::clear() {
        for (auto& entry : cache) {
            entry.second.clear();   // 像素只归缓存所有,pack 里拿的是共享同一块 data 的浅拷贝
        }
        cache.clear();
        pack.clear();
        return *this;
    }
}
