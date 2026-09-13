namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::edge_both(float size) {
        private_edge_pick(label.edge_both, size);
        return *this;
    }
}
