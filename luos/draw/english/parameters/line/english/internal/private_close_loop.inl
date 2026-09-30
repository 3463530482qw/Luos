namespace Gnik_luos {
    // 收尾:末点没回到起点时补一段"末点 → 起点",它算在整条弧长的最后
    void Draw_line_cmd::private_close_loop(double passed, bool tailing) {
        if (!tailing) {
            return;
        }
        const Line_point& head = private_path.front();
        const Line_point& tail = private_path.back();
        private_dash_begin = passed;
        private_u0 = (private_path_length > 0.0) ? passed / private_path_length : 0.0;
        private_u1 = 1.0;
        private_segment_colors(head, true);
        private_segment(tail.x, tail.y, head.x, head.y);
    }
}
