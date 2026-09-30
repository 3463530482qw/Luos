namespace Gnik_luos {
    // 逐段推进管线:进度按累计弧长分配,虚线相位也顺着弧长接下去
    // 端头只有整条路径的两个自由头,中间拐角不封;返回整条路径累计到的弧长
    double Draw_line_cmd::private_advance_path() {
        const size_t last = private_path.size() - 1;
        double passed = 0.0;
        for (size_t index = 1; index < private_path.size(); index++) {
            const Line_point& begin = private_path[index - 1];
            const Line_point& end = private_path[index];
            const double dx = end.x - begin.x;
            const double dy = end.y - begin.y;
            const double length = std::sqrt(dx * dx + dy * dy);
            private_dash_begin = passed;
            private_u0 = (private_path_length > 0.0) ? passed / private_path_length : 0.0;
            passed += length;
            private_u1 = (private_path_length > 0.0) ? passed / private_path_length : 1.0;
            private_segment_colors(end, private_trailing || index == last);
            private_cap_begin = private_edge_on && index == 1;
            private_cap_end = private_edge_on && index == last;
            private_segment(begin.x, begin.y, end.x, end.y);
        }
        private_cap_begin = false;
        private_cap_end = false;
        return passed;
    }
}
