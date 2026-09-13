namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::edge_round_notch(float size) {
        private_edge_pick(label.edge_round_notch, size);
        return *this;
    }
}
