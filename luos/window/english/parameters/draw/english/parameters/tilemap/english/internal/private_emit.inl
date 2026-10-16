namespace Gnik_luos {
    // 一格摊成两个三角形:列向右、行向下,世界 y 向上所以行往下走
    void Tilemap::private_emit(int column, int row, int tile_value) {
        if (tile_value < 0 || tile_value >= sprite_sheet.count) {
            return;   // 图集里没有这一格:不出顶点
        }
        const double left = static_cast<double>(origin_x) + static_cast<double>(column) * static_cast<double>(tile_size);
        const double top = static_cast<double>(origin_y) - static_cast<double>(row) * static_cast<double>(tile_size);
        const double right = left + static_cast<double>(tile_size);
        const double bottom = top - static_cast<double>(tile_size);
        const float cell_u = 1.0f / static_cast<float>(sprite_sheet.columns);
        const float cell_v = 1.0f / static_cast<float>(sprite_sheet.rows);
        const int cell_column = tile_value % sprite_sheet.columns;
        const int cell_row = tile_value / sprite_sheet.columns;
        const float u0 = static_cast<float>(cell_column) * cell_u;
        const float v0 = static_cast<float>(cell_row) * cell_v;
        const float u1 = u0 + cell_u;
        const float v1 = v0 + cell_v;

        const Vector3 corner[4]{
            Vector3{left, top, 0.0},
            Vector3{right, top, 0.0},
            Vector3{right, bottom, 0.0},
            Vector3{left, bottom, 0.0}
        };
        const int triangle[6]{0, 1, 2, 0, 2, 3};
        const float u[4]{u0, u1, u1, u0};
        const float v[4]{v0, v0, v1, v1};   // 与图片命令同一口径:上边给 v0(图集顶行)
        for (int step = 0; step < 6; step++) {
            const int index = triangle[step];
            Vertex vertex{};
            vertex.x = static_cast<float>(corner[index].x);
            vertex.y = static_cast<float>(corner[index].y);
            vertex.z = 0.0f;
            vertex.u = u[index];
            vertex.v = v[index];
            vertex.r = r / 255.0f;
            vertex.g = g / 255.0f;
            vertex.b = b / 255.0f;
            vertex.a = a;
            vertex.use_texture = 1.0f;   // 与图片命令同一档:贴图 × 顶点色
            cache.push_back(vertex);
        }
    }
}
