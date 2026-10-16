namespace Gnik_luos {
    // 一个字形(或没绑字体时的占位方块)摊成两个三角形
    // 位图左上角 = 笔位 + 偏移,基线下移;再按旋转中心转四个角;uv 要给反过来(图集/贴图的 v = 0 在顶行,世界 y 越往上越大)
    void Text::private_emit(const Glyph& glyph, float pen_x, float baseline, bool placeholder, float box_width, float box_height) {
        double left = 0.0;
        double top = 0.0;
        double right = 0.0;
        double bottom = 0.0;
        float u0 = 0.0f;
        float v0 = 0.0f;
        float u1 = 0.0f;
        float v1 = 0.0f;
        if (placeholder) {
            left = static_cast<double>(pen_x);
            top = static_cast<double>(baseline);
            right = left + static_cast<double>(box_width);
            bottom = top - static_cast<double>(box_height);
            u0 = 0.0f;
            v0 = 0.0f;   // 整张贴图铺满一个方块
            u1 = 1.0f;
            v1 = 1.0f;
        } else {
            if (glyph.width <= 0.0f || glyph.height <= 0.0f) {
                return;   // 空白字形:没有位图要出
            }
            left = static_cast<double>(pen_x) + static_cast<double>(glyph.offset_x);
            top = static_cast<double>(baseline) + static_cast<double>(glyph.offset_y);
            right = left + static_cast<double>(glyph.width);
            bottom = top - static_cast<double>(glyph.height);
            u0 = glyph.u0;
            v0 = glyph.v0;
            u1 = glyph.u1;
            v1 = glyph.v1;
        }

        Vector3 corner[4]{
            Vector3{left, top, static_cast<double>(z1)},
            Vector3{right, top, static_cast<double>(z1)},
            Vector3{right, bottom, static_cast<double>(z1)},
            Vector3{left, bottom, static_cast<double>(z1)}
        };
        const Vector3 pivot{rotation_point_x, rotation_point_y, rotation_point_z};
        if (rotation_x != 0.0f || rotation_y != 0.0f || rotation_z != 0.0f) {
            for (int index = 0; index < 4; index++) {
                corner[index] = private_rotate_vector(corner[index], pivot);
            }
        }

        const int triangle[6]{0, 1, 2, 0, 2, 3};
        // uv 与角序对齐:上面两个角给 v0(位图顶行)、下面两个角给 v1 —— 与图片命令同一口径
        const float u[4]{u0, u1, u1, u0};
        const float v[4]{v0, v0, v1, v1};
        for (int step = 0; step < 6; step++) {
            const int index = triangle[step];
            Vertex vertex{};
            vertex.x = static_cast<float>(corner[index].x);
            vertex.y = static_cast<float>(corner[index].y);
            vertex.z = static_cast<float>(corner[index].z);
            vertex.u = u[index];
            vertex.v = v[index];
            vertex.r = r / 255.0f;
            vertex.g = g / 255.0f;
            vertex.b = b / 255.0f;
            vertex.a = a;
            vertex.use_texture = 1.0f;   // 与图片命令同一档:贴图 × 顶点色(图集 RGB 是白的,乘上去正好是字色;覆盖率在 alpha 里)
            cache.push_back(vertex);
        }
    }
}
