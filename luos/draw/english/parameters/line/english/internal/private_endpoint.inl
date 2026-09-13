namespace Gnik_luos {
    void Draw_line_cmd::private_endpoint() {
        private_ax = private_sx;
        private_ay = private_sy;
        private_bx = private_ex;
        private_by = private_ey;
        if (!private_cap_begin && !private_cap_end) {
            return;
        }
        float dx = private_ex - private_sx;
        float dy = private_ey - private_sy;
        float length = std::sqrt(dx * dx + dy * dy);
        if (length <= 0.0f) {
            return;
        }
        // 封边:端头按摆位回缩;回缩量不超过半段长,免得短段把自己翻过来
        float retract = std::min(private_cap_retract, length * 0.5f);
        float step_x = dx / length * retract;
        float step_y = dy / length * retract;
        if (private_cap_begin) {
            private_ax += step_x;
            private_ay += step_y;
        }
        if (private_cap_end) {
            private_bx -= step_x;
            private_by -= step_y;
        }
    }
}
