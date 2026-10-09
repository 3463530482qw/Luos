namespace Gnik_luos {
    void Line::update() {
        if (!dirty) {
            return;   // 参数没动:顶点还是上一次算的,不重算
        }
        private_build_frame();   // 轴与截面坐标系先落定:退化判定要用长度,路由里的旋转与摊角都要用它
        cache.clear();
        if (!line_empty(private_length, size_x, size_y)) {
            cache.resize(36);   // 一个立体:六个面十二个三角形
        }
        private_rebuild_route();
        private_run_route();
        dirty = false;
    }
}
