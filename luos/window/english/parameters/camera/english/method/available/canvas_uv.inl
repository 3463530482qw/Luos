namespace Gnik_luos {
    // 世界点 → 画布内的归一化坐标:0 是矩形左上角,1 是右下角(越界就落在 0~1 之外,不夹取)
    Vector3 Camera::canvas_uv(const Vector3& world) const {
        const Canvas_rect canvas = canvas_rect();
        const double width = canvas.max_x - canvas.min_x;
        const double height = canvas.max_y - canvas.min_y;
        return Vector3{
            (width > 0.0) ? (world.x - canvas.min_x) / width : 0.0,
            (height > 0.0) ? (world.y - canvas.min_y) / height : 0.0,
            world.z - canvas.z
        };
    }
}
