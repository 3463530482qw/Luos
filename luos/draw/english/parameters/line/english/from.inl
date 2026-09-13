namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::from(float x, float y) {
        // 丢掉之前画的路径,当前点落在这里
        private_point.clear();
        private_point.push_back(Line_point{x, y, r, g, b, a});
        private_trailing = false;
        x1 = x;
        y1 = y;
        x2 = x;
        y2 = y;
        cmd_update = true;
        return *this;
    }
}
