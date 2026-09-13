namespace Gnik_luos {
    const std::vector<Vertex>& Draw_line_cmd::vertex() const {
        // 缓存内容 = 最近一次 Draw::draw 按当时的参数与标志算出的几何
        return private_vertex;
    }
}
