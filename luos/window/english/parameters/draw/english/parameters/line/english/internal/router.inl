namespace Gnik_luos {
    void Line::private_rebuild_route() {
        private_step_count = cache.empty() ? 0 : 3;   // 退化线没有顶点可铺,路由一步都不装
    }
}
