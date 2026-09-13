namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::line_width(float width) {
        thickness = width;
        cmd_update = true;
        return *this;
    }
}
