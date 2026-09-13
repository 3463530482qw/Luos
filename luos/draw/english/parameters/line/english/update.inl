namespace Gnik_luos {
    void Draw_line_cmd::update() {
        router();
        private_vertex.clear();
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
        private_path_length = 0.0f;
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
    }
}
