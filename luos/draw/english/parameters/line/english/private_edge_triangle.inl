namespace Gnik_luos {
    // 铺一个三角形(第 4 个点与第 3 个点重合,像素化时照样能当四边形处理)
    void Draw_line_cmd::private_edge_triangle(const std::array<std::array<float, 2>, 4>& corner) {
        if (label.pixelated && pixel_size > 0.0f) {
            private_pixel_cells(corner, private_u0, private_u0);
            return;
        }
        for (int index = 0; index < 3; index++) {
            private_vertex.push_back(Vertex{corner[index][0], corner[index][1], private_u0, 0.0f});
        }
    }
}
