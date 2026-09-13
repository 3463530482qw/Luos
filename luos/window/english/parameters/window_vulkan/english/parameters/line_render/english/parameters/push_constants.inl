namespace Gnik_luos {
    struct Line_push_constants {   // 推常量:布局须与 line.vert 一致(mat4 mvp + 3 float,共 76B)
        float mvp[16];
        float screen_w, screen_h, snap_pixel;
    };
}
