namespace Gnik_luos {
    // 四个角摊成两个三角形:角序 0 左下 → 1 右下 → 2 右上 → 3 左上;管线不剔背面,绕序反过来也照常画
    // uv 也按这套角序:v = 0 在上,图不会倒
    void Picture::private_quad() {
        const double corner_uv[4][2]{{0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}, {0.0, 0.0}};
        const int triangle[6]{0, 1, 2, 0, 2, 3};
        const float texture_flag = use_texture ? 1.0f : 0.0f;
        for (int step = 0; step < 6; step++) {
            const int corner = triangle[step];
            Vertex& vertex = cache[step];
            vertex.x = static_cast<float>(private_corner[corner].x);
            vertex.y = static_cast<float>(private_corner[corner].y);
            vertex.z = static_cast<float>(private_corner[corner].z);
            vertex.u = static_cast<float>(corner_uv[corner][0]);
            vertex.v = static_cast<float>(corner_uv[corner][1]);
            vertex.r = r[corner] / 255.0f;
            vertex.g = g[corner] / 255.0f;
            vertex.b = b[corner] / 255.0f;
            vertex.a = a[corner];
            vertex.use_texture = texture_flag;
        }
    }
}
