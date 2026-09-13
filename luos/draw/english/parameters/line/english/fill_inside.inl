namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::fill_inside(uint8_t red, uint8_t green, uint8_t blue, float alpha) {
        inside_color = {red, green, blue};
        inside_alpha = alpha;
        label.fill_inside = true;
        cmd_update = true;
        return *this;
    }
}
