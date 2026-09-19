namespace Gnik_luos {
    // u 写线段进度,颜色留给颜色步骤填
    void Draw_line_cmd::private_quad(float ax, float ay, float bx, float by, float u0, float u1) {
        if (label.pixelated && pixel_size > 0.0f) {
            const std::array<std::array<float, 2>, 4> corner{{
                {ax + private_nx, ay + private_ny},
                {bx + private_nx, by + private_ny},
                {bx - private_nx, by - private_ny},
                {ax - private_nx, ay - private_ny}
            }};
            private_pixel_cells(corner, u0, u1);
            return;
        }
        Vertex corner[4] = {
            {ax + private_nx, ay + private_ny, 0.0f, u0, 0.0f},
            {bx + private_nx, by + private_ny, 0.0f, u1, 0.0f},
            {bx - private_nx, by - private_ny, 0.0f, u1, 0.0f},
            {ax - private_nx, ay - private_ny, 0.0f, u0, 0.0f}
        };
        const int tri[6] = {0, 1, 2, 0, 2, 3};
        for (int i = 0; i < 6; i++) {
            private_vertex.push_back(corner[tri[i]]);
        }
    }
}
