namespace Gnik_luos {
    void Draw_line_cmd::private_connect() {
        // 拐角外侧的缺口是四边形:p1(上一段外侧角点)、斜接点、p2(本段外侧角点)、拐点
        // 斜接点取两条外侧偏移线的交点,太尖就沿拐点方向截断(退化成斜切)
        if (!private_prev_valid || thickness <= 0.0f) {
            return;
        }
        float d1x = private_prev_dx;
        float d1y = private_prev_dy;
        float d2x = private_dx;
        float d2y = private_dy;
        float turn = d1x * d2y - d1y * d2x;
        if (std::fabs(turn) < 0.0001f) {
            return;   // 直着接,本来就没有缺口
        }
        float half = private_half_width;
        float o1x = (turn > 0.0f) ?  d1y : -d1y;
        float o1y = (turn > 0.0f) ? -d1x :  d1x;
        float o2x = (turn > 0.0f) ?  d2y : -d2y;
        float o2y = (turn > 0.0f) ? -d2x :  d2x;
        float bx = private_ax;
        float by = private_ay;
        float p1x = bx + o1x * half;
        float p1y = by + o1y * half;
        float p2x = bx + o2x * half;
        float p2y = by + o2y * half;
        float t = ((p2x - p1x) * d2y - (p2y - p1y) * d2x) / turn;
        float mx = p1x + d1x * t;
        float my = p1y + d1y * t;
        float reach = std::sqrt((mx - bx) * (mx - bx) + (my - by) * (my - by));
        float limit = half * 4.0f;
        if (reach > limit) {
            float shrink = limit / reach;
            mx = bx + (mx - bx) * shrink;
            my = by + (my - by) * shrink;
        }
        if (label.pixelated && pixel_size > 0.0f) {
            const std::array<std::array<float, 2>, 4> corner{{
                {p1x, p1y}, {mx, my}, {p2x, p2y}, {bx, by}
            }};
            private_pixel_cells(corner, private_u0, private_u0);
            return;
        }
        if (corner_smooth > 0.0f) {
            // 拐点圆角:路径不动,只把外侧那个角从斜接点收成一段圆弧
            // 圆滑度 0 就是斜接点,1 收到半径 = 半线宽的圆弧(round join 那种)
            float outer_x = mx - bx;
            float outer_y = my - by;
            float outer_length = std::sqrt(outer_x * outer_x + outer_y * outer_y);
            if (outer_length > 0.0001f) {
                outer_x /= outer_length;
                outer_y /= outer_length;
                float peak_reach = outer_length + (half - outer_length) * corner_smooth;
                float peak_x = bx + outer_x * peak_reach;
                float peak_y = by + outer_y * peak_reach;
                // 过 p1、peak、p2 的圆,从圆心把 p1 扫到 p2
                float a2 = p1x * p1x + p1y * p1y;
                float b2 = peak_x * peak_x + peak_y * peak_y;
                float c2 = p2x * p2x + p2y * p2y;
                float divisor = 2.0f * (p1x * (peak_y - p2y) + peak_x * (p2y - p1y) + p2x * (p1y - peak_y));
                if (std::fabs(divisor) > 0.0001f) {
                    float center_x = (a2 * (peak_y - p2y) + b2 * (p2y - p1y) + c2 * (p1y - peak_y)) / divisor;
                    float center_y = (a2 * (p2x - peak_x) + b2 * (p1x - p2x) + c2 * (peak_x - p1x)) / divisor;
                    float radius = std::sqrt((p1x - center_x) * (p1x - center_x) + (p1y - center_y) * (p1y - center_y));
                    float start = std::atan2(p1y - center_y, p1x - center_x);
                    float middle = std::atan2(peak_y - center_y, peak_x - center_x);
                    float end = std::atan2(p2y - center_y, p2x - center_x);
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
                    return;
                }
            }
        }
        Vertex corner[6] = {
            {p1x, p1y, private_u0, 0.0f},
            {mx,  my,  private_u0, 0.0f},
            {p2x, p2y, private_u0, 0.0f},
            {p1x, p1y, private_u0, 0.0f},
            {p2x, p2y, private_u0, 0.0f},
            {bx,  by,  private_u0, 0.0f}
        };
        for (int i = 0; i < 6; i++) {
            private_vertex.push_back(corner[i]);
        }
    }
}
