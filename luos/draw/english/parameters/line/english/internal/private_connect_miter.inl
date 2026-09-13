namespace Gnik_luos {
    // 斜接补角:用四边形(p1、斜接点、p2、拐点)把拐角外侧的缺口盖上;像素化时这四边形走格子
    void Draw_line_cmd::private_connect_miter() {
        if (label.pixelated && pixel_size > 0.0f) {
            private_pixel_cells(private_corner, private_u0, private_u0);
            return;
        }
        const int order[6] = {0, 1, 2, 0, 2, 3};
        for (int index = 0; index < 6; index++) {
            const std::array<float, 2>& point = private_corner[order[index]];
            private_vertex.push_back(Vertex{point[0], point[1], private_u0, 0.0f});
        }
    }
}
