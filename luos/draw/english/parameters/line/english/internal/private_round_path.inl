namespace Gnik_luos {
    // 拐点圆角:把路径上段与段相接的那个角按圆滑度切成圆弧,切点落在两条边上,弧与两边相切
    // 结果放进 private_path —— 线本身的几何和填充都按这条圆角后的路径算
    void Draw_line_cmd::private_round_path() {
        private_path = private_point;
        if (corner_smooth <= 0.0f || private_point.size() < 3) {
            return;
        }
        const int steps = 6;
        private_path.clear();
        private_path.push_back(private_point.front());
        for (size_t index = 1; index + 1 < private_point.size(); index++) {
            const Line_point& from = private_point[index - 1];
            const Line_point& corner = private_point[index];
            const Line_point& to = private_point[index + 1];
            float in_x = corner.x - from.x;
            float in_y = corner.y - from.y;
            float out_x = to.x - corner.x;
            float out_y = to.y - corner.y;
            float in_length = std::sqrt(in_x * in_x + in_y * in_y);
            float out_length = std::sqrt(out_x * out_x + out_y * out_y);
            if (in_length <= 0.0001f || out_length <= 0.0001f) {
                private_path.push_back(corner);
                continue;
            }
            in_x /= in_length;
            in_y /= in_length;
            out_x /= out_length;
            out_y /= out_length;
            float turn = in_x * out_y - in_y * out_x;
            float cosine = std::clamp(in_x * out_x + in_y * out_y, -1.0f, 1.0f);
            float half = (3.14159265f - std::acos(cosine)) * 0.5f;   // 转角的一半
            if (std::fabs(turn) < 0.0001f || half <= 0.0001f) {
                private_path.push_back(corner);   // 直着接,没有角可圆
                continue;
            }
            // 切点各退 圆滑度 × 能退的最大距离(不超过两条短线的一半,短段不会翻过来)
            float tangent = corner_smooth * std::min(in_length, out_length) * 0.5f;
            float radius = tangent / std::tan(half);
            float left_x = corner.x - in_x * tangent;
            float left_y = corner.y - in_y * tangent;
            float right_x = corner.x + out_x * tangent;
            float right_y = corner.y + out_y * tangent;
            // 圆心在角平分线上,偏向转弯那一侧
            float side = (turn > 0.0f) ? 1.0f : -1.0f;
            float center_x = left_x - in_y * radius * side;
            float center_y = left_y + in_x * radius * side;
            Line_point point = corner;
            point.x = left_x;
            point.y = left_y;
            private_path.push_back(point);
            float start = std::atan2(left_y - center_y, left_x - center_x);
            float end = std::atan2(right_y - center_y, right_x - center_x);
            while (end - start > 3.14159265f) {
                end -= 6.28318531f;
            }
            while (end - start < -3.14159265f) {
                end += 6.28318531f;
            }
            for (int step = 1; step <= steps; step++) {
                float angle = start + (end - start) * (static_cast<float>(step) / steps);
                point.x = center_x + radius * std::cos(angle);
                point.y = center_y + radius * std::sin(angle);
                private_path.push_back(point);
            }
        }
        private_path.push_back(private_point.back());
    }
}
