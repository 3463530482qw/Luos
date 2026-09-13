namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::connect(bool on) {
        label.connected = on;
        cmd_update = true;
        return *this;
    }
}
