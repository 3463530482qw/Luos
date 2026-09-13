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
        float half = thickness * 0.5f;
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
