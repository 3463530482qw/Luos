namespace Gnik_luos {
    void Line::private_run_route() {
        if (private_step_count == 0) {
            return;
        }
        size_t offset = 0;
        for (size_t index = 0; index + 1 < private_point.size(); index++) {
            private_build_frame(index);   // 逐段定轴与截面朝向:折线每段方向各不相同
            if (private_length <= 0.0) {
                continue;   // 零长段不出顶点,后面的段顺次往前补
            }
            private_rotate();   // 第一步:绕旋转中心把这段转过去
            private_box(offset);   // 第二步:八个角摊成六个面
            offset += 36;
        }
        private_rgba();   // 第三步:整条折线统一落色
    }
}
