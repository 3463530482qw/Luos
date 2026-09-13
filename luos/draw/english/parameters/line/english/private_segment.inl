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
    }
}
