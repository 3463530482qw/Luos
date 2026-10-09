namespace Gnik_luos {
    // 屏幕点(设备像素)→ 画布上的世界点:取这条像素射线与画布平面(z = canvas.z)的交点,
    // 再夹进画布矩形(画布外取最近边界);拾取画布上的东西就用它,别再拿地面交点换算
    // 屏幕像素里那个灰边偏移由调用方先减掉(窗口层知道内接矩形从哪开始)
    Vector3 Camera::canvas_from_screen(double screen_x, double screen_y, double screen_width, double screen_height) const {
        const Canvas_rect canvas = canvas_rect();
        const World_ray ray = ray_through_screen(screen_x, screen_y, screen_width, screen_height);
        const double depth = (ray.direction.z != 0.0) ? (canvas.z - ray.origin.z) / ray.direction.z : 0.0;
        const double world_x = ray.origin.x + ray.direction.x * depth;
        const double world_y = ray.origin.y + ray.direction.y * depth;
        return Vector3{
            std::min(std::max(world_x, canvas.min_x), canvas.max_x),
            std::min(std::max(world_y, canvas.min_y), canvas.max_y),
            canvas.z
        };
    }
}
