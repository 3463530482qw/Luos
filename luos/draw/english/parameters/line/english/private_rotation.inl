namespace Gnik_luos {
    void Draw_line_cmd::private_rotation() {
        // 与旧版 fontemit 同朝向
        float cosr = std::cos(rotate);
        float sinr = std::sin(rotate);
        float dx = private_sx - rox;
        float dy = private_sy - roy;
        private_ax = rox + dx * cosr - dy * sinr;
        private_ay = roy + dx * sinr + dy * cosr;
        dx = private_ex - rox;
        dy = private_ey - roy;
        private_bx = rox + dx * cosr - dy * sinr;
        private_by = roy + dx * sinr + dy * cosr;
    }
}
