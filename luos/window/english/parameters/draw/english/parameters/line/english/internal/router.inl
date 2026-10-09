namespace Gnik_luos {
    void Line::private_rebuild_route() {
        private_step_count = cache.empty() ? 0 : 3;   // 没段可铺就没顶点,路由一步都不装
    }
}
