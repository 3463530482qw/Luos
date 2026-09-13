namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::end(bool on) {
        ended = on;
        cmd_update = true;
        return *this;
    }
}
