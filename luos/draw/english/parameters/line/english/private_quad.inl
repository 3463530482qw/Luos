namespace Gnik_luos {
    // u 写线段进度,颜色留给颜色步骤填
    void Draw_line_cmd::private_quad(float ax, float ay, float bx, float by, float u0, float u1) {
        Vertex corner[4] = {
            {ax + private_nx, ay + private_ny, u0, 0.0f},
            {bx + private_nx, by + private_ny, u1, 0.0f},
            {bx - private_nx, by - private_ny, u1, 0.0f},
            {ax - private_nx, ay - private_ny, u0, 0.0f}
        };
        const int tri[6] = {0, 1, 2, 0, 2, 3};
        for (int i = 0; i < 6; i++) {
            private_vertex.push_back(corner[tri[i]]);
        }
    }
}
