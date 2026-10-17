namespace Gnik_luos {
    // 路由:按脏标记装步骤(与 Line / Window 同一写法),分派在 run.inl
    void Picture::private_rebuild_route() {
        private_route.clear();
        if (!private_ready) {
            return;   // 没给到两个角:这张图不成立,库里不替它编形状,一条都不装
        }
        private_route.push_back([this]() {
            // 图是平的:四个角都取第一个点的 z,只有 x/y 按两个对角摊开;角序 0 左上 → 1 右上 → 2 右下 → 3 左下
            private_corner[0] = Vector3{x1, y2, z1};
            private_corner[1] = Vector3{x2, y2, z1};
            private_corner[2] = Vector3{x2, y1, z1};
            private_corner[3] = Vector3{x1, y1, z1};
        });
        private_route.push_back([this]() {
            private_rotate();   // 绕旋转中心把这四个角转过去
        });
        private_route.push_back([this]() {
            cache.resize(6);    // 一张图 = 两个三角形
            private_quad();     // 四个角摊成四边形
        });
    }
}
