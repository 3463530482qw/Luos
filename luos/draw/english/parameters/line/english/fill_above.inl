namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::fill_above(bool on) {
        label.fill_above = on;
        cmd_update = true;
        return *this;
    }
}
