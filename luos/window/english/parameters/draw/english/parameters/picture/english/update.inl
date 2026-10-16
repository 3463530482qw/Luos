namespace Gnik_luos {
    void Picture::update() {
        if (!dirty) {
            return;   // 参数没动:顶点还是上一次算的,不重算
        }
        cache.clear();
        if (!private_ready) {
            dirty = false;
            return;   // 没给到两个角:这张图不成立,库里不替它编形状
        }
        // 图是平的:四个角都取第一个点的 z,只有 x/y 按两个对角摊开
        private_corner[0] = Vector3{x1, y1, z1};
        private_corner[1] = Vector3{x2, y1, z1};
        private_corner[2] = Vector3{x2, y2, z1};
        private_corner[3] = Vector3{x1, y2, z1};
        private_rotate();
        cache.resize(6);
        private_quad();
        dirty = false;
    }
}
