namespace Gnik_luos {
    // 一整条路径的重算:路由 → 清缓存 → 量弧长 → 逐段推进 → 补首尾接头
    // 各步的细节分别在 private_measure_path / private_advance_path / private_close_loop 里
    void Draw_line_cmd::update() {
        router();
        private_vertex.clear();
        private_fill_vertex.clear();
        // 每次重算都从"没有上一段"起,否则起头会冒出一个接头
        private_prev_valid = false;
        private_first_valid = false;
        // 拐点圆角(改路径本身那种)以后再做:private_round_path 先不接上
        private_path = private_point;
        // 填充单独成层:算好交给 Draw 排在全部线条之前,只填充不画线也行
        private_fill_inside();
        private_fill_outside();
        private_edge_place();
        if (private_step.empty()) {
            return;
        }
        if (private_path.size() < 2) {
            // 没走链条:画变量给的那一条,两头都是开放的端头
            private_u0 = 0.0f;
            private_u1 = 1.0f;
            private_path_length = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
            private_dash_begin = 0.0f;
            private_er = r;
            private_eg = g;
            private_eb = b;
            private_ea = a;
            private_cap_begin = private_edge_on;
            private_cap_end = private_edge_on;
            private_segment(x1, y1, x2, y2);
            return;
        }

        const Line_point& head = private_path.front();
        const Line_point& tail = private_path.back();
        const double tail_dx = head.x - tail.x;
        const double tail_dy = head.y - tail.y;
        const bool tailing = ended && std::sqrt(tail_dx * tail_dx + tail_dy * tail_dy) > 0.0;
        private_measure_path(tailing);
        const double passed = private_advance_path();
        private_close_loop(passed, tailing);

        // 首尾之间再补一个接头(末段或补出来的收尾段,与首段相接)
        if (!ended || !label.connected || label.dashed || !private_prev_valid || !private_first_valid) {
            return;
        }
        private_ax = private_first_ax;
        private_ay = private_first_ay;
        private_dx = private_first_dx;
        private_dy = private_first_dy;
        private_u0 = 0.0f;
        private_emit_begin = private_vertex.size();
        private_segment_colors(head, true);
        private_connect();
        if (label.gradient) {
            private_gradient();
        } else {
            private_single_color();
        }
    }
}
