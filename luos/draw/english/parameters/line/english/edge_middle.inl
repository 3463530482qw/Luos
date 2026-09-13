namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::edge_middle(float size) {
        private_edge_pick(label.edge_middle, size);
        return *this;
    }
}
