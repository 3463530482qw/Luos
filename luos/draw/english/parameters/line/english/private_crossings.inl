namespace Gnik_luos {
    // 水平线 y 与路径各边的交点 x,升序;偶数奇数配对就是形状内部的一段
    // 边跨过 y 才算(端点归上半开区间),水平边与退化边自然被排除
    void Draw_line_cmd::private_crossings(float y, std::vector<float>& out) const {
        out.clear();
        size_t count = private_path.size();
        for (size_t index = 0; index < count; index++) {
            const Line_point& begin = private_path[index];
            const Line_point& end = private_path[(index + 1) % count];
            if ((begin.y <= y) == (end.y <= y)) {
                continue;
            }
            float t = (y - begin.y) / (end.y - begin.y);
            out.push_back(begin.x + (end.x - begin.x) * t);
        }
        std::sort(out.begin(), out.end());
    }
}
