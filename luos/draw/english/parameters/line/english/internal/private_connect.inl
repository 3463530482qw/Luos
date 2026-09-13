namespace Gnik_luos {
    void Draw_line_cmd::private_connect() {
        // 拐角外侧的缺口:private_corner = [p1 上一段外侧角点, 斜接点, p2 本段外侧角点, 拐点 B]
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
        private_corner[0] = {bx + o1x * half, by + o1y * half};
        private_corner[2] = {bx + o2x * half, by + o2y * half};
        float t = ((private_corner[2][0] - private_corner[0][0]) * d2y - (private_corner[2][1] - private_corner[0][1]) * d2x) / turn;
        float mx = private_corner[0][0] + d1x * t;
        float my = private_corner[0][1] + d1y * t;
        float reach = std::sqrt((mx - bx) * (mx - bx) + (my - by) * (my - by));
        float limit = half * 4.0f;
        if (reach > limit) {
            float shrink = limit / reach;
            mx = bx + (mx - bx) * shrink;
            my = by + (my - by) * shrink;
        }
        private_corner[1] = {mx, my};
        private_corner[3] = {bx, by};
        // 圆滑度开着才把角收圆,否则就是原来的斜接补角
        if (corner_smooth > 0.0f) {
            private_connect_round();
            return;
        }
        private_connect_miter();
    }
}
