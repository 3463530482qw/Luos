namespace Gnik_luos {
    void Draw_line_cmd::private_fill_inside() {
        // 内部填充:按顶点 y 把形状切成水平梯形带,每带的交点按偶奇规则配成段再铺四边形
        // 边界都是直线段,梯形带与形状贴合;凹形状、自交形状(例如原路折回的尖刺)也不会多填
        if (!label.fill_inside || private_path.size() < 3) {
            return;
        }
        if (label.pixelated && pixel_size > 0.0f) {
            // 像素化:逐格行采样,行中心落在形状里才铺这一行,列也按格心取
            float min_y = private_path.front().y;
            float max_y = private_path.front().y;
            for (const Line_point& point : private_path) {
                min_y = std::min(min_y, point.y);
                max_y = std::max(max_y, point.y);
            }
            std::vector<float> crossing{};
            int first_row = static_cast<int>(std::floor(min_y / pixel_size));
            int last_row = static_cast<int>(std::ceil(max_y / pixel_size)) - 1;
            for (int row = first_row; row <= last_row; row++) {
                private_crossings((static_cast<float>(row) + 0.5f) * pixel_size, crossing);
                for (size_t index = 0; index + 1 < crossing.size(); index += 2) {
                    private_pixel_rect(
                        private_pixel_col(crossing[index]),
                        private_pixel_col(crossing[index + 1]) - 1,
                        row,
                        inside_color,
                        inside_alpha
                    );
                }
            }
            return;
        }
        std::vector<float> cut{};
        cut.reserve(private_path.size());
        for (const Line_point& point : private_path) {
            cut.push_back(point.y);
        }
        std::sort(cut.begin(), cut.end());
        cut.erase(std::unique(cut.begin(), cut.end()), cut.end());
        float red = inside_color[0] / 255.0f;
        float green = inside_color[1] / 255.0f;
        float blue = inside_color[2] / 255.0f;
        float alpha = inside_alpha;
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
        std::vector<std::array<float, 2>> span{};
        for (size_t band = 0; band + 1 < cut.size(); band++) {
            float top = cut[band];
            float bottom = cut[band + 1];
            if (bottom - top <= 0.0001f) {
                continue;
            }
            private_band_spans(top, bottom, span);
            for (size_t index = 0; index + 1 < span.size(); index += 2) {
                emit(span[index][0], top, span[index + 1][0], top, span[index + 1][1], bottom, span[index][1], bottom);
            }
        }
    }
}
