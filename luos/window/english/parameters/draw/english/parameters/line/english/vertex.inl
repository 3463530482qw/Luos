namespace Gnik_luos {
    const std::vector<Vertex>& Line::vertex() const {
        // 缓存内容 = 最近一次 update 按当时参数算出的几何
        return cache;
    }
}
