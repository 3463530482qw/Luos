namespace Gnik_luos {
    // 封边是冲突项:开一个就把别的关掉;与 end 同时开直接报错
    void Draw_line_cmd::private_edge_pick(bool& mode, float size) {
        if (ended) {
            throw std::runtime_error("Draw_line_cmd::private_edge_pick => 封边与 end 不能同时开");
        }
        label.edge_rect = false;
        label.edge_top = false;
        label.edge_middle = false;
        label.edge_bottom = false;
        label.edge_both = false;
        mode = true;
        edge_size = size;
        cmd_update = true;
    }
}
