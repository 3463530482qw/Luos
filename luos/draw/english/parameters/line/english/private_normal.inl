namespace Gnik_luos {
    void Draw_line_cmd::private_normal() {
        // 长度记 0 表示退化段,后面的出点步骤据此跳过
        float dx = private_bx - private_ax;
        float dy = private_by - private_ay;
        private_length = std::sqrt(dx * dx + dy * dy);
        if (private_length <= 0.0f || thickness <= 0.0f) {
            private_length = 0.0f;
            private_nx = 0.0f;
            private_ny = 0.0f;
            private_dx = 0.0f;
            private_dy = 0.0f;
            return;
        }
        float half = thickness * 0.5f;
        private_nx = -dy / private_length * half;
        private_ny =  dx / private_length * half;
        private_dx = dx / private_length;
        private_dy = dy / private_length;
    }
}
