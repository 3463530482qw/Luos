namespace Gnik_luos {
    // 四个角摊成两个三角形:角序 0 左上 → 1 右上 → 2 右下 → 3 左下;管线不剔背面,绕序反过来也照常画
    // uv:不切图就是整张的 0~1;切了图就取图集里那一格(上边给 v0 —— 与地图图层、文字同一口径)
    void Picture::private_quad() {
        float u0 = 0.0f;
        float v0 = 0.0f;
        float u1 = 1.0f;
        float v1 = 1.0f;
        if (sprite_sheet.count > 1) {
            const float cell_u = 1.0f / static_cast<float>(sprite_sheet.columns);
            const float cell_v = 1.0f / static_cast<float>(sprite_sheet.rows);
            u0 = static_cast<float>(sheet_index % sprite_sheet.columns) * cell_u;
            v0 = static_cast<float>(sheet_index / sprite_sheet.columns) * cell_v;
            u1 = u0 + cell_u;
            v1 = v0 + cell_v;
        }
        const float corner_u[4]{u0, u1, u1, u0};
        const float corner_v[4]{v0, v0, v1, v1};
        const int triangle[6]{0, 1, 2, 0, 2, 3};
        const float texture_flag = use_texture ? 1.0f : 0.0f;
        for (int step = 0; step < 6; step++) {
            const int corner = triangle[step];
            Vertex& vertex = cache[step];
            vertex.x = static_cast<float>(private_corner[corner].x);
            vertex.y = static_cast<float>(private_corner[corner].y);
            vertex.z = static_cast<float>(private_corner[corner].z);
            vertex.u = corner_u[corner];
            vertex.v = corner_v[corner];
            vertex.r = r[corner] / 255.0f;
            vertex.g = g[corner] / 255.0f;
            vertex.b = b[corner] / 255.0f;
            vertex.a = a[corner];
            vertex.use_texture = texture_flag;
        }
    }
}
