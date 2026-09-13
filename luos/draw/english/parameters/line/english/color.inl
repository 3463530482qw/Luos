namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::color(uint8_t red, uint8_t green, uint8_t blue, float alpha) {
        // 两端同色并关掉渐变;链尾改色算给整条路径,写在某个 to() 之前则只给那一段
        private_trailing = (private_point.size() >= 2);
        r = {red, red};
        g = {green, green};
        b = {blue, blue};
        a = {alpha, alpha};
        label.gradient = false;
        cmd_update = true;
        return *this;
    }
}
