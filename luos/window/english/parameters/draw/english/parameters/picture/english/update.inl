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
        // 图是平的:四个角都取第一个点的 z,只有 x/y 按两个对角摊开;角序 0 左上 → 1 右上 → 2 右下 → 3 左下
        private_corner[0] = Vector3{x1, y2, z1};   // 左上(世界 y 向上,起点取高的那个 y)
        private_corner[1] = Vector3{x2, y2, z1};   // 右上
        private_corner[2] = Vector3{x2, y1, z1};   // 右下
        private_corner[3] = Vector3{x1, y1, z1};   // 左下
        private_rotate();
        cache.resize(6);
        private_quad();
        dirty = false;
    }
}
