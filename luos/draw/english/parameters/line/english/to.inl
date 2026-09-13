namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::to(float x, float y) {
        // 从最后一个顶点延长一段;没 from 过就把当前起点当作链条头
        if (private_point.empty()) {
            private_point.push_back(Line_point{x1, y1, r, g, b, a});
        }
        x1 = private_point.back().x;
        y1 = private_point.back().y;
        x2 = x;
        y2 = y;
        private_point.push_back(Line_point{x, y, r, g, b, a});
        private_trailing = false;
        cmd_update = true;
        return *this;
    }
}
