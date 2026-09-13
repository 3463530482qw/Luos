namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::edge_rect(bool on) {
        label.edge_rect = on;
        label.edge_top = false;
        label.edge_middle = false;
        label.edge_bottom = false;
        label.edge_both = false;
        cmd_update = true;
        return *this;
    }
}
