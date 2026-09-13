namespace Gnik_luos {
    // 封边:上/中/下 在端头接一个等腰三角形,尖落在延伸点上;上下一块 是三角形负形
    // 圆滑度 > 0 时把尖改成相切圆角(切点退到两条边上,弧两边都不外扩);半圆正/负形就是圆滑度 1 的那种
    void Draw_line_cmd::private_edge_cap() {
        if (!private_edge_on || private_length <= 0.0f) {
            return;
        }
        // 相切圆角:在 tip 处的夹角里切一段弧,切点 P1/P2 落在两条边上
        // 返回的弧按角度扫,凸角(正形)时弧朝 tip 外鼓,凹角(负形)时弧往回收
        auto fillet = [&](float from_x, float from_y, float tip_x, float tip_y, float to_x, float to_y,
                          float& p1_x, float& p1_y, float& p2_x, float& p2_y,
                          float& center_x, float& center_y, float& radius, float& peak_x, float& peak_y) {
            float left_x = from_x - tip_x;
            float left_y = from_y - tip_y;
            float right_x = to_x - tip_x;
            float right_y = to_y - tip_y;
            float left_length = std::sqrt(left_x * left_x + left_y * left_y);
            float right_length = std::sqrt(right_x * right_x + right_y * right_y);
            if (left_length <= 0.0001f || right_length <= 0.0001f) {
                return false;
            }
            float ux = left_x / left_length;
            float uy = left_y / left_length;
            float vx = right_x / right_length;
            float vy = right_y / right_length;
            float cosine = std::clamp(ux * vx + uy * vy, -1.0f, 1.0f);
            float half = std::acos(cosine) * 0.5f;   // 夹角的一半
            if (half <= 0.0001f || half >= 1.57079632f) {
                return false;
            }
            float tangent_limit = std::min(left_length, right_length);
            float tangent = tangent_limit * corner_smooth;   // 圆滑度 1 时切到能切的最靠里
            radius = tangent * std::tan(half);
            float bisector_x = ux + vx;
            float bisector_y = uy + vy;
            float bisector_length = std::sqrt(bisector_x * bisector_x + bisector_y * bisector_y);
            if (bisector_length <= 0.0001f) {
                return false;
            }
            bisector_x /= bisector_length;
            bisector_y /= bisector_length;
            p1_x = tip_x + ux * tangent;
            p1_y = tip_y + uy * tangent;
            p2_x = tip_x + vx * tangent;
            p2_y = tip_y + vy * tangent;
            center_x = tip_x + bisector_x * (radius / std::sin(half));
            center_y = tip_y + bisector_y * (radius / std::sin(half));
            peak_x = center_x - bisector_x * radius;
            peak_y = center_y - bisector_y * radius;
            return true;
        };
        // 从 a 扫到 b 的弧(fan 原点给 origin),扫过的方向经过 peak
        auto sweep = [&](float center_x, float center_y, float radius, float peak_x, float peak_y,
                         float ax, float ay, float bx, float by, float origin_x, float origin_y) {
            const int steps = 6;
            float start = std::atan2(ay - center_y, ax - center_x);
            float middle = std::atan2(peak_y - center_y, peak_x - center_x);
            float end = std::atan2(by - center_y, bx - center_x);
            // 三个角都折到 peak 附近(相差不超过半圈),从 a 扫到 b 就一定经过 peak
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
            float previous_x = ax;
            float previous_y = ay;
            for (int index = 1; index <= steps; index++) {
                float angle = start + (end - start) * (static_cast<float>(index) / steps);
                float x = center_x + radius * std::cos(angle);
                float y = center_y + radius * std::sin(angle);
                private_edge_triangle({{{origin_x, origin_y}, {previous_x, previous_y}, {x, y}, {x, y}}});
                previous_x = x;
                previous_y = y;
            }
        };
        for (int side = 0; side < 2; side++) {
            bool at_begin = (side == 0);
            if (at_begin ? !private_cap_begin : !private_cap_end) {
                continue;
            }
            float sign = at_begin ? -1.0f : 1.0f;   // 朝外的方向
            float base_x = at_begin ? private_ax : private_bx;   // 回缩后的端头(底边中点)
            float base_y = at_begin ? private_ay : private_by;
            float end_x = at_begin ? private_sx : private_ex;    // 回缩前的端头
            float end_y = at_begin ? private_sy : private_ey;
            float outer_a_x = end_x + private_nx;
            float outer_a_y = end_y + private_ny;
            float outer_b_x = end_x - private_nx;
            float outer_b_y = end_y - private_ny;
            if (private_cap_notch) {
                // 负形:两块尖压在端面两侧,往回收缩到中线上的同一点;圆角是把这个凹角填圆
                float inner_a_x = base_x;
                float inner_a_y = base_y;
                float inner_b_x = base_x;
                float inner_b_y = base_y;
                float center_x = 0.0f;
                float center_y = 0.0f;
                float radius = 0.0f;
                float peak_x = 0.0f;
                float peak_y = 0.0f;
                bool rounded = (corner_smooth > 0.0f)
                    && fillet(outer_a_x, outer_a_y, base_x, base_y, outer_b_x, outer_b_y,
                              inner_a_x, inner_a_y, inner_b_x, inner_b_y, center_x, center_y, radius, peak_x, peak_y);
                const std::array<std::array<float, 2>, 4> prong_a{{
                    {base_x + private_nx, base_y + private_ny}, {outer_a_x, outer_a_y}, {inner_a_x, inner_a_y}, {inner_a_x, inner_a_y}
                }};
                const std::array<std::array<float, 2>, 4> prong_b{{
                    {base_x - private_nx, base_y - private_ny}, {outer_b_x, outer_b_y}, {inner_b_x, inner_b_y}, {inner_b_x, inner_b_y}
                }};
                private_edge_triangle(prong_a);
                private_edge_triangle(prong_b);
                if (rounded) {
                    // 凹角填圆:弧与两条边围出来的那块补上去
                    private_edge_triangle({{{base_x, base_y}, {inner_a_x, inner_a_y}, {inner_b_x, inner_b_y}, {inner_b_x, inner_b_y}}});
                    sweep(center_x, center_y, radius, peak_x, peak_y, inner_a_x, inner_a_y, inner_b_x, inner_b_y, base_x, base_y);
                }
                continue;
            }
            float tip_x = base_x + private_dx * private_cap_forward * sign + private_cap_lateral * private_nx;
            float tip_y = base_y + private_dy * private_cap_forward * sign + private_cap_lateral * private_ny;
            float left_x = base_x + private_nx;
            float left_y = base_y + private_ny;
            float right_x = base_x - private_nx;
            float right_y = base_y - private_ny;
            float cut_left_x = tip_x;
            float cut_left_y = tip_y;
            float cut_right_x = tip_x;
            float cut_right_y = tip_y;
            float center_x = 0.0f;
            float center_y = 0.0f;
            float radius = 0.0f;
            float peak_x = 0.0f;
            float peak_y = 0.0f;
            bool rounded = (corner_smooth > 0.0f)
                && fillet(left_x, left_y, tip_x, tip_y, right_x, right_y,
                          cut_left_x, cut_left_y, cut_right_x, cut_right_y, center_x, center_y, radius, peak_x, peak_y);
            if (rounded) {
                // 凸角抹圆:两条边各退到切点,中间用相切弧接上;弧不会拱出封边的轮廓
                private_edge_triangle({{{left_x, left_y}, {cut_left_x, cut_left_y}, {cut_right_x, cut_right_y}, {cut_right_x, cut_right_y}}});
                sweep(center_x, center_y, radius, peak_x, peak_y, cut_left_x, cut_left_y, cut_right_x, cut_right_y, left_x, left_y);
                private_edge_triangle({{{left_x, left_y}, {cut_right_x, cut_right_y}, {right_x, right_y}, {right_x, right_y}}});
                continue;
            }
            const std::array<std::array<float, 2>, 4> cap{{
                {left_x, left_y},
                {right_x, right_y},
                {tip_x, tip_y},
                {tip_x, tip_y}
            }};
            private_edge_triangle(cap);
        }
    }
}
