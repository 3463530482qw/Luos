namespace Gnik_luos {
    // 圆角补角:路径不动,只把拐角外侧那个角从斜接点收成一段圆弧
    // 圆滑度 0 等于斜接点(不会走到这里),1 收到半径 = 半线宽(round join 那种),中间按比例插值
    void Draw_line_cmd::private_connect_round() {
        float bx = private_corner[3][0];
        float by = private_corner[3][1];
        float p1x = private_corner[0][0];
        float p1y = private_corner[0][1];
        float p2x = private_corner[2][0];
        float p2y = private_corner[2][1];
        float outer_x = private_corner[1][0] - bx;
        float outer_y = private_corner[1][1] - by;
        float outer_length = std::sqrt(outer_x * outer_x + outer_y * outer_y);
        if (outer_length <= 0.0001f) {
            private_connect_miter();
            return;
        }
        outer_x /= outer_length;
        outer_y /= outer_length;
        float peak_reach = outer_length + (private_half_width - outer_length) * corner_smooth;
        float peak_x = bx + outer_x * peak_reach;
        float peak_y = by + outer_y * peak_reach;
        // 过 p1、peak、p2 的圆
        float a2 = p1x * p1x + p1y * p1y;
        float b2 = peak_x * peak_x + peak_y * peak_y;
        float c2 = p2x * p2x + p2y * p2y;
        float divisor = 2.0f * (p1x * (peak_y - p2y) + peak_x * (p2y - p1y) + p2x * (p1y - peak_y));
        if (std::fabs(divisor) <= 0.0001f) {
            private_connect_miter();
            return;
        }
        float center_x = (a2 * (peak_y - p2y) + b2 * (p2y - p1y) + c2 * (p1y - peak_y)) / divisor;
        float center_y = (a2 * (p2x - peak_x) + b2 * (p1x - p2x) + c2 * (peak_x - p1x)) / divisor;
        float radius = std::sqrt((p1x - center_x) * (p1x - center_x) + (p1y - center_y) * (p1y - center_y));
        float start = std::atan2(p1y - center_y, p1x - center_x);
        float middle = std::atan2(peak_y - center_y, peak_x - center_x);
        float end = std::atan2(p2y - center_y, p2x - center_x);
        // 三个角都折到 peak 附近(相差不超过半圈),从 p1 扫到 p2 就一定经过 peak
        while (start - middle > 3.14159265f) {
            start -= 6.28318531f;
        }
        while (start - middle < -3.14159265f) {
            start += 6.28318531f;
        }
        while (end - middle > 3.14159265f) {
            end -= 6.28318531f;
        }
        while (end - middle < -3.14159265f) {
            end += 6.28318531f;
        }
        const int steps = 10;
        float previous_x = p1x;
        float previous_y = p1y;
        for (int index = 1; index <= steps; index++) {
            // 两端强制落在原来的角点上,免得弧算出来差一点点留缝
            float x = p2x;
            float y = p2y;
            if (index < steps) {
                float angle = start + (end - start) * (static_cast<float>(index) / steps);
                x = center_x + radius * std::cos(angle);
                y = center_y + radius * std::sin(angle);
            }
            Vertex slice[3] = {
                {bx, by, private_u0, 0.0f},
                {previous_x, previous_y, private_u0, 0.0f},
                {x, y, private_u0, 0.0f}
            };
            for (int i = 0; i < 3; i++) {
                private_vertex.push_back(slice[i]);
            }
            previous_x = x;
            previous_y = y;
        }
    }
}
