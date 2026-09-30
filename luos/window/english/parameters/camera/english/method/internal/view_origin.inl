namespace Gnik_luos {
    // 相机在视图空间里的"站位":相机自己站在画布矩形中心的正后方,
    // 于是视图空间的原点正好落在画布中心 —— 正交取景框(±半宽/±半高)与画布矩形严丝合缝。
    // 透视档只借它的朝向与位置,矩形中心偏移在本帧相机里就是视线正前方
    Vector3 Camera::private_view_origin() const {
        const Canvas_rect canvas = canvas_rect();
        return Vector3{
            (canvas.min_x + canvas.max_x) * 0.5,
            (canvas.min_y + canvas.max_y) * 0.5,
            canvas.z
        };
    }
}
