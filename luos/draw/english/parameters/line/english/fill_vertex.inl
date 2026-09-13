namespace Gnik_luos {
    const std::vector<Vertex>& Draw_line_cmd::fill_vertex() const {
        // 填充不跟线条混在一起:Draw::draw 会把它插到全部线条之前
        return private_fill_vertex;
    }
}
