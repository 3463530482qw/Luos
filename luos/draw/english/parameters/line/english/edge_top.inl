namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::edge_top(float size) {
        private_edge_pick(label.edge_top, size);
        return *this;
    }
}
