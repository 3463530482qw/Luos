namespace Gnik_luos {
    struct Ground_push_constants {   // 推常量:布局须与 ground.vert / ground.frag 一致(mat4 + 4 个 vec4,共 128B)
        float mvp[16];
        float minor_color[4];
        float major_color[4];
        float grid_params[4];   // x = 小格边长, y = 每几格一条主线, z = 淡出距离, w = 地面四边形半径
        float eye_ground[4];    // xy = 相机在地面上的投影
    };
}
