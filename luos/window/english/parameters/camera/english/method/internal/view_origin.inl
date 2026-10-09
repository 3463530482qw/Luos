namespace Gnik_luos {
    // 画布矩形的中心(世界坐标,落在画布平面上):rect() 把画布四角按当前朝向摆开时以它为锚点
    // 视图空间的原点不在这里 —— 那是相机站位(position),view_matrix 与 ray_through_screen 都用它
    Vector3 Camera::private_view_origin() const {
        const Canvas_rect canvas = canvas_rect();
        return Vector3{
            (canvas.min_x + canvas.max_x) * 0.5,
            (canvas.min_y + canvas.max_y) * 0.5,
            canvas.z
        };
    }
}
