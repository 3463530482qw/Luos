namespace Gnik_luos {
    void Line::private_run_route() {
        if (private_step_count == 0) {
            return;
        }
        private_direction();   // 第一步:算单位方向与线宽半宽法线
        private_quad();        // 第二步:四个角摊成两个三角形
        private_rgba();        // 第三步:落色
    }
}
