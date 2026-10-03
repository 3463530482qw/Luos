namespace Gnik_luos {
    void Line::private_rebuild_route() {
        route = {};
        if (cache.empty()) {
            return;   // 退化线没有顶点可铺,路由一步都不装
        }
        route.step[0] = &Line::private_direction;
        route.step[1] = &Line::private_quad;
        route.step[2] = &Line::private_rgba;
        route.count = 3;
    }
}
