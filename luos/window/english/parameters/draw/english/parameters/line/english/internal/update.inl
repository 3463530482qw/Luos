namespace Gnik_luos {
    void Line::update() {
        if (!dirty) {
            return;   // 参数没动:顶点还是上一次算的,不重算
        }
        private_dx = x2 - x1;
        private_dy = y2 - y1;
        private_length = std::sqrt(private_dx * private_dx + private_dy * private_dy);
        cache.clear();
        if (!line_empty(private_length, thickness)) {
            cache.resize(6);   // 一条线一个四边形:两个三角形六个顶点
        }
        private_rebuild_route();
        private_run_route();
        dirty = false;
    }
}
