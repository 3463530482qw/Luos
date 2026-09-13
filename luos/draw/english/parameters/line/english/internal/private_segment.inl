namespace Gnik_luos {
    void Draw_line_cmd::private_segment(float start_x, float start_y, float end_x, float end_y) {
        // emit_begin 圈定本段顶点,颜色步骤只染这一段
        private_sx = start_x;
        private_sy = start_y;
        private_ex = end_x;
        private_ey = end_y;
        private_emit_begin = private_vertex.size();
        for (void (Draw_line_cmd::*step)() : private_step) {
            (this->*step)();
        }
        if (!private_prev_valid && private_length > 0.0f) {
            // 本次重算里的第一段:闭合时补首尾接头要用它的起点与方向
            private_first_ax = private_ax;
            private_first_ay = private_ay;
            private_first_dx = private_dx;
            private_first_dy = private_dy;
            private_first_valid = true;
        }
        // 本段方向留给下一段补接头
        private_prev_dx = private_dx;
        private_prev_dy = private_dy;
        private_prev_valid = (private_length > 0.0f);
    }
}
