namespace Gnik_luos {
    struct Line_push_constants {   // 推常量:布局须与 line.vert 一致(mat4 mvp + 5 float,共 84B)
        float mvp[16];
        float screen_w, screen_h, snap_pixel;
        float texture_scale_x, texture_scale_y;   // 顶点里的 uv 是世界单位,乘上它才是展开图的归一坐标
    };
}
