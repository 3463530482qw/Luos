namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::fill_outside(uint8_t red, uint8_t green, uint8_t blue, float alpha) {
        outside_color = {red, green, blue};
        outside_alpha = alpha;
        label.fill_outside = true;
        cmd_update = true;
        return *this;
    }
}
