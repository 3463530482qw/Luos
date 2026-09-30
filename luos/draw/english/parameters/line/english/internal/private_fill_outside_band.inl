namespace Gnik_luos {
    // 梯形带通路:和内部填充同一套带子,每带把形状占掉的段跳过去,剩下的就是矩形里形状之外的部分
    void Draw_line_cmd::private_fill_outside_band(float view_left, float view_top, float view_right, float view_bottom) {
        std::vector<float> cut{view_top, view_bottom};
        cut.reserve(private_path.size() + 2);
        for (const Line_point& point : private_path) {
            cut.push_back(point.y);
        }
        std::sort(cut.begin(), cut.end());
        cut.erase(std::unique(cut.begin(), cut.end()), cut.end());

        const float red = outside_color[0] / 255.0f;
        const float green = outside_color[1] / 255.0f;
        const float blue = outside_color[2] / 255.0f;
        const float alpha = outside_alpha;
        auto emit = [&](float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy) {
            const Vertex corner[6] = {
                {ax, ay, 0.0f, 0.0f, 0.0f, red, green, blue, alpha},
                {bx, by, 0.0f, 0.0f, 0.0f, red, green, blue, alpha},
                {cx, cy, 0.0f, 0.0f, 0.0f, red, green, blue, alpha},
                {ax, ay, 0.0f, 0.0f, 0.0f, red, green, blue, alpha},
                {cx, cy, 0.0f, 0.0f, 0.0f, red, green, blue, alpha},
                {dx, dy, 0.0f, 0.0f, 0.0f, red, green, blue, alpha}
            };
            for (const Vertex& point : corner) {
                private_fill_vertex.push_back(point);
            }
        };
        // 外侧段的两端夹进矩形,越出画面的部分交给视口也行,这里先夹掉省得白铺
        auto clamp = [&](float value) {
            return std::min(std::max(value, view_left), view_right);
        };
        auto outer = [&](float left_top, float left_bottom, float right_top, float right_bottom, float top, float bottom) {
            const float ax = clamp(left_top);
            const float ay = clamp(left_bottom);
            const float bx = clamp(right_top);
            const float by = clamp(right_bottom);
            if (bx <= ax && by <= ay) {
                return;   // 这一带被形状占满,没有外侧
            }
            emit(ax, top, bx, top, by, bottom, ay, bottom);
        };

        std::vector<std::array<float, 2>> span{};
        for (size_t band = 0; band + 1 < cut.size(); band++) {
            const float top = std::max(cut[band], view_top);
            const float bottom = std::min(cut[band + 1], view_bottom);
            if (bottom - top <= 0.0001f) {
                continue;
            }
            private_band_spans(top, bottom, span);
            float left_top = view_left;       // 上一段结束处的上下两端
            float left_bottom = view_left;
            for (size_t index = 0; index + 1 < span.size(); index += 2) {
                outer(left_top, left_bottom, span[index][0], span[index][1], top, bottom);
                left_top = span[index + 1][0];
                left_bottom = span[index + 1][1];
            }
            outer(left_top, left_bottom, view_right, view_right, top, bottom);
        }
    }
}
