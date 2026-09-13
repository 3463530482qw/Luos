namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::gradient(
        uint8_t start_red, uint8_t start_green, uint8_t start_blue,
        uint8_t end_red, uint8_t end_green, uint8_t end_blue,
        float start_alpha, float end_alpha
    ) {
        // 链尾改色算给整条路径,写在某个 to() 之前则只给那一段(与 color 同一口径)
        private_trailing = (private_point.size() >= 2);
        r = {start_red, end_red};
        g = {start_green, end_green};
        b = {start_blue, end_blue};
        a = {start_alpha, end_alpha};
        label.gradient = true;
        cmd_update = true;
        return *this;
    }
}
