namespace Gnik_luos {
    void Draw_line_cmd::update() {
        router();
        private_vertex.clear();
        private_fill_vertex.clear();
        // 每次重算都从"没有上一段"起,否则起头会冒出一个接头
        private_prev_valid = false;
        private_first_valid = false;
        // 填充单独成层:算好交给 Draw 排在全部线条之前,只填充不画线也行
        private_fill_inside();
        private_fill_outside();
        if (private_step.empty()) {
            return;
        }
        if (private_point.size() < 2) {
            // 没走链条:画变量给的那一条
            private_u0 = 0.0f;
            private_u1 = 1.0f;
            private_path_length = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
            private_dash_begin = 0.0f;
            private_er = r;
            private_eg = g;
            private_eb = b;
            private_ea = a;
            private_segment(x1, y1, x2, y2);
            return;
        }
        const Line_point& head = private_point.front();
        const Line_point& tail = private_point.back();
        // 收尾:末点没回到起点时补一段末点→起点
        float tail_dx = head.x - tail.x;
        float tail_dy = head.y - tail.y;
        float tail_length = std::sqrt(tail_dx * tail_dx + tail_dy * tail_dy);
        bool tailing = ended && tail_length > 0.0f;
        private_path_length = tailing ? tail_length : 0.0f;
        for (size_t index = 1; index < private_point.size(); index++) {
            float dx = private_point[index].x - private_point[index - 1].x;
            float dy = private_point[index].y - private_point[index - 1].y;
            private_path_length += std::sqrt(dx * dx + dy * dy);
        }
        // 逐段跑管线:进度按累计弧长分配,虚线相位也顺着弧长接下去
        const size_t last = private_point.size() - 1;
        float passed = 0.0f;
        for (size_t index = 1; index < private_point.size(); index++) {
            const Line_point& begin = private_point[index - 1];
            const Line_point& end = private_point[index];
            float dx = end.x - begin.x;
            float dy = end.y - begin.y;
            float length = std::sqrt(dx * dx + dy * dy);
            private_dash_begin = passed;
            private_u0 = (private_path_length > 0.0f) ? passed / private_path_length : 0.0f;
            passed += length;
            private_u1 = (private_path_length > 0.0f) ? passed / private_path_length : 1.0f;
            private_segment_colors(end, private_trailing || index == last);
            private_segment(begin.x, begin.y, end.x, end.y);
        }
        if (tailing) {
            private_dash_begin = passed;
            private_u0 = (private_path_length > 0.0f) ? passed / private_path_length : 0.0f;
            private_u1 = 1.0f;
            private_segment_colors(head, true);
            private_segment(tail.x, tail.y, head.x, head.y);
        }
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
