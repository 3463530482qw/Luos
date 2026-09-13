namespace Gnik_luos {
    void Draw_line_cmd::private_fill_outside() {
        // 外部填充:相机画面矩形挖掉形状本身
        // 和内部填充同一套梯形带,每带把形状占掉的段跳过去,剩下的就是画面里形状之外的部分
        if (!label.fill_outside || camera == nullptr || private_point.size() < 3) {
            return;
        }
        View_rect view = camera->view();
        std::vector<float> cut{view.top, view.bottom};
        cut.reserve(private_point.size() + 2);
        for (const Line_point& point : private_point) {
            cut.push_back(point.y);
        }
        std::sort(cut.begin(), cut.end());
        cut.erase(std::unique(cut.begin(), cut.end()), cut.end());
        float red = outside_color[0] / 255.0f;
        float green = outside_color[1] / 255.0f;
        float blue = outside_color[2] / 255.0f;
        float alpha = outside_alpha;
        auto emit = [&](float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy) {
            const Vertex corner[6] = {
                {ax, ay, 0.0f, 0.0f, red, green, blue, alpha},
                {bx, by, 0.0f, 0.0f, red, green, blue, alpha},
                {cx, cy, 0.0f, 0.0f, red, green, blue, alpha},
                {ax, ay, 0.0f, 0.0f, red, green, blue, alpha},
                {cx, cy, 0.0f, 0.0f, red, green, blue, alpha},
                {dx, dy, 0.0f, 0.0f, red, green, blue, alpha}
            };
            for (const Vertex& point : corner) {
                private_fill_vertex.push_back(point);
            }
        };
        // 外侧段的两端夹进画面矩形,越出画面的部分交给视口也行,这里先夹掉省得白铺
        auto clamp = [&](float value) {
            return std::min(std::max(value, view.left), view.right);
        };
        auto outer = [&](float left_top, float left_bottom, float right_top, float right_bottom, float top, float bottom) {
            float ax = clamp(left_top);
            float ay = clamp(left_bottom);
            float bx = clamp(right_top);
            float by = clamp(right_bottom);
            if (bx <= ax && by <= ay) {
                return;   // 这一带被形状占满,没有外侧
            }
            emit(ax, top, bx, top, by, bottom, ay, bottom);
        };
        std::vector<std::array<float, 2>> span{};
        for (size_t band = 0; band + 1 < cut.size(); band++) {
            float top = std::max(cut[band], view.top);
            float bottom = std::min(cut[band + 1], view.bottom);
            if (bottom - top <= 0.0001f) {
                continue;
            }
            private_band_spans(top, bottom, span);
            float left_top = view.left;       // 上一段结束处的上下两端
            float left_bottom = view.left;
            for (size_t index = 0; index + 1 < span.size(); index += 2) {
                outer(left_top, left_bottom, span[index][0], span[index][1], top, bottom);
                left_top = span[index + 1][0];
                left_bottom = span[index + 1][1];
            }
            outer(left_top, left_bottom, view.right, view.right, top, bottom);
        }
    }
}
