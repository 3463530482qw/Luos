namespace Gnik_luos {
    // 忘掉一条路径的像素:重新生成过贴图文件之后必须调,否则 find 给的还是旧像素
    Image& Image::forget(const std::string& path) {
        auto it = cache.find(path);
        if (it == cache.end()) {
            return *this;
        }
        it->second.clear();
        cache.erase(it);
        return *this;
    }
}
