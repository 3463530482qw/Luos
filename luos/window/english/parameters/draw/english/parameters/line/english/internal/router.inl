namespace Gnik_luos {
    // 路由:按脏标记装步骤(与 Window_time / Window 的 router 同一写法),分派在 run.inl
    void Line::private_rebuild_route() {
        private_route.clear();
        if (private_valid.empty()) {
            return;   // 没段可铺:一条都不装
        }
        private_route.push_back([this]() {
            for (size_t ordinal = 0; ordinal < private_valid.size(); ordinal++) {
                private_build_frame(private_valid[ordinal]);   // 逐段定轴与截面朝向:折线每段方向各不相同
                private_segment.push_back(private_length);     // 逐段长度:渲染侧靠它算每段每面那些块的尺寸
                private_rotate();   // 绕旋转中心把这段转过去
                private_box(private_vertex_begin[ordinal], ordinal);   // 八个角摊成留下的那些面
            }
        });
        private_route.push_back([this]() {
            private_rgba();   // 整条折线统一落色
        });
    }
}
