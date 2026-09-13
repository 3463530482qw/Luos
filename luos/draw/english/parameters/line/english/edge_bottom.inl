namespace Gnik_luos {
    Draw_line_cmd& Draw_line_cmd::edge_bottom(float size) {
        private_edge_pick(label.edge_bottom, size);
        return *this;
    }
}
