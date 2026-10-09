namespace Gnik_luos {
    void Line::private_run_route() {
        if (private_step_count == 0) {
            return;
        }
        private_rotate();   // 第一步:绕旋转中心把整根线转过去
        private_box();      // 第二步:八个角摊成六个面
        private_rgba();     // 第三步:落色
    }
}
