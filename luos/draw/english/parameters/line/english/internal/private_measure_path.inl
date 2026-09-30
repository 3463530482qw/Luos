namespace Gnik_luos {
    // 整条路径的弧长:先按顺序累加各段,末点没回到起点且要求收尾时再把"末→首"那一段算进去
    void Draw_line_cmd::private_measure_path(bool tailing) {
        const Line_point& head = private_path.front();
        const Line_point& tail = private_path.back();
        const double tail_dx = head.x - tail.x;
        const double tail_dy = head.y - tail.y;
        const double tail_length = std::sqrt(tail_dx * tail_dx + tail_dy * tail_dy);
        private_path_length = tailing ? tail_length : 0.0;

        for (size_t index = 1; index < private_path.size(); index++) {
            const double dx = private_path[index].x - private_path[index - 1].x;
            const double dy = private_path[index].y - private_path[index - 1].y;
            private_path_length += std::sqrt(dx * dx + dy * dy);
        }
    }
}
