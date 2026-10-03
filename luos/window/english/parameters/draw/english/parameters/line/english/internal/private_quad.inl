namespace Gnik_luos {
    void Line::private_quad() {
        // 两端各自带自己的 z 与进度 u:四边形的四个角按 [起点+法线, 终点+法线, 终点-法线, 起点-法线]
        const Vertex corner[4] = {
            {x1 + private_nx, y1 + private_ny, z1, 0.0f, 0.0f},
            {x2 + private_nx, y2 + private_ny, z2, 1.0f, 0.0f},
            {x2 - private_nx, y2 - private_ny, z2, 1.0f, 0.0f},
            {x1 - private_nx, y1 - private_ny, z1, 0.0f, 0.0f}
        };
        const int tri[6] = {0, 1, 2, 0, 2, 3};
        for (int index = 0; index < 6; index++) {
            cache[static_cast<size_t>(index)] = corner[tri[index]];
        }
    }
}
