namespace Gnik_luos {
    void Draw_line_cmd::private_dashed() {
        // 按整条路径的弧长切分,跨段相位连续
        if (private_length <= 0.0f) {
            return;
        }
        float dx = private_bx - private_ax;
        float dy = private_by - private_ay;
        float pattern = dash_length + dash_gap;
        if (pattern <= 0.0f) {
            private_quad(private_ax, private_ay, private_bx, private_by, private_u0, private_u1);
            return;
        }
        float segment_begin = private_dash_begin;
        float segment_end = segment_begin + private_length;
        float span = (private_path_length > 0.0f) ? private_path_length : private_length;
        for (float dash_begin = std::floor(segment_begin / pattern) * pattern; dash_begin < segment_end; dash_begin += pattern) {
            float begin = std::max(dash_begin, segment_begin);
            float end = std::min(dash_begin + dash_length, segment_end);
            if (end <= begin) {
                continue;
            }
            float begin_ratio = (begin - segment_begin) / private_length;
            float end_ratio = (end - segment_begin) / private_length;
            private_quad(
                private_ax + dx * begin_ratio, private_ay + dy * begin_ratio,
                private_ax + dx * end_ratio,   private_ay + dy * end_ratio,
                begin / span, end / span
            );
        }
    }
}
