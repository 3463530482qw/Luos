namespace Gnik_luos {
    // 相机在视图空间里的"站位":相机站在画布矩形中心的正后方,视图空间原点因此落在矩形中心
    //   正交档:取景框(±半宽/±半高)与画布矩形严丝合缝
    //   透视档:视锥也以这一点为顶点,所以反投影(ray_through_screen)必须用同一个点当射线起点,
    //          否则"按像素拾取"和渲染矩阵不是同一台相机(这是之前的 bug)
    Vector3 Camera::private_view_origin() const {
        const Canvas_rect canvas = canvas_rect();
        return Vector3{
            (canvas.min_x + canvas.max_x) * 0.5,
            (canvas.min_y + canvas.max_y) * 0.5,
            canvas.z
        };
    }
}
