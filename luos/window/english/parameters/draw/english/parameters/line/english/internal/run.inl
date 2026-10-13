namespace Gnik_luos {
    void Line::private_run_route() {
        if (private_step_count == 0) {
            return;
        }
        for (size_t ordinal = 0; ordinal < private_valid.size(); ordinal++) {
            private_build_frame(private_valid[ordinal]);   // 逐段定轴与截面朝向:折线每段方向各不相同
            private_segment.push_back(private_length);     // 逐段长度:渲染侧靠它算每段每面那些块的尺寸
            private_rotate();   // 第一步:绕旋转中心把这段转过去
            private_box(private_vertex_begin[ordinal], ordinal);   // 第二步:八个角摊成留下的那些面
        }
        private_rgba();   // 第三步:整条折线统一落色
    }
}
