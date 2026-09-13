namespace Gnik_luos {
    // 把一块凸四边形按网格铺成方块:行中心落在四边形里才铺这一行,列按格心取整格
    // 等于把画面降到 画布/像素大小 的分辨率再放大,斜边因此成为台阶
    void Draw_line_cmd::private_pixel_cells(const std::array<std::array<float, 2>, 4>& corner, float u0, float u1) {
        if (pixel_size <= 0.0f) {
            return;
        }
        float min_y = corner[0][1];
        float max_y = corner[0][1];
        for (int index = 1; index < 4; index++) {
            min_y = std::min(min_y, corner[index][1]);
            max_y = std::max(max_y, corner[index][1]);
        }
        // u 按格心在四边形长边方向上的投影插值,渐变才不会被压成一色
        float ax = corner[0][0];
        float ay = corner[0][1];
        float dx = corner[1][0] - ax;
        float dy = corner[1][1] - ay;
        float length2 = dx * dx + dy * dy;
        auto span_at = [&](float y, float& out_left, float& out_right) {
            bool hit = false;
            for (int index = 0; index < 4; index++) {
                const std::array<float, 2>& begin = corner[index];
                const std::array<float, 2>& end = corner[(index + 1) % 4];
                if ((begin[1] <= y) == (end[1] <= y)) {
                    continue;   // 不跨这条水平线(水平边与退化边都落在这里)
                }
                float x = begin[0] + (end[0] - begin[0]) * ((y - begin[1]) / (end[1] - begin[1]));
                if (!hit) {
                    out_left = x;
                    out_right = x;
                    hit = true;
                } else {
                    out_left = std::min(out_left, x);
                    out_right = std::max(out_right, x);
                }
            }
            return hit;
        };
        int first_row = static_cast<int>(std::floor(min_y / pixel_size));
        int last_row = static_cast<int>(std::ceil(max_y / pixel_size)) - 1;
        for (int row = first_row; row <= last_row; row++) {
            float y = (static_cast<float>(row) + 0.5f) * pixel_size;
            float left = 0.0f;
            float right = 0.0f;
            if (!span_at(y, left, right)) {
                continue;
            }
            int first_col = private_pixel_col(left);
            int last_col = private_pixel_col(right) - 1;
            if (last_col < first_col) {
                continue;
            }
            float top = static_cast<float>(row) * pixel_size;
            float bottom = top + pixel_size;
            float x0 = static_cast<float>(first_col) * pixel_size;
            float x1 = static_cast<float>(last_col + 1) * pixel_size;
            const std::array<std::array<float, 2>, 4> cell{{
                {x0, top}, {x1, top}, {x1, bottom}, {x0, bottom}
            }};
            for (int index = 0; index < 6; index++) {
                static const int order[6] = {0, 1, 2, 0, 2, 3};
                const std::array<float, 2>& point = cell[order[index]];
                float u = u0;
                if (length2 > 0.0f && u0 != u1) {
                    u = u0 + (u1 - u0) * ((point[0] - ax) * dx + (point[1] - ay) * dy) / length2;
                }
                private_vertex.push_back(Vertex{point[0], point[1], u, 0.0f});
            }
        }
    }
}
