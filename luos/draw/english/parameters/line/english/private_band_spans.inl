namespace Gnik_luos {
    // 取一条水平带 [top, bottom] 里每个跨带边的上下两端 x,按带内 x 升序
    // 相邻两项配对就是形状内部的一段(偶奇规则);带的边界都取在顶点 y 上,所以边只会整条跨带
    void Draw_line_cmd::private_band_spans(float top, float bottom, std::vector<std::array<float, 2>>& out) const {
        out.clear();
        size_t count = private_point.size();
        for (size_t index = 0; index < count; index++) {
            const Line_point& begin = private_point[index];
            const Line_point& end = private_point[(index + 1) % count];
            bool spans = (begin.y <= top && end.y >= bottom) || (end.y <= top && begin.y >= bottom);
            if (!spans) {
                continue;   // 不跨带(水平边、退化边都落在这一支)
            }
            float dy = end.y - begin.y;
            float top_x = begin.x + (end.x - begin.x) * ((top - begin.y) / dy);
            float bottom_x = begin.x + (end.x - begin.x) * ((bottom - begin.y) / dy);
            out.push_back({top_x, bottom_x});
        }
        std::sort(out.begin(), out.end(), [](const std::array<float, 2>& left, const std::array<float, 2>& right) {
            return (left[0] + left[1]) < (right[0] + right[1]);
        });
    }
}
