namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::end(bool on) {
        if (on && (label.edge_top || label.edge_middle || label.edge_bottom || label.edge_both)) {
            throw std::runtime_error("Draw_line_cmd::end => end 与封边不能同时开");
        }
        ended = on;
        cmd_update = true;
        return *this;
    }
}
