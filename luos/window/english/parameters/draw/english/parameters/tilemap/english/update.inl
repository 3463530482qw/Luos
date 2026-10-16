namespace Gnik_luos {
    void Tilemap::update() {
        if (!dirty) {
            return;   // 参数没动:顶点还是上一次算的
        }
        cache.clear();
        private_layout();
        dirty = false;
    }
}
