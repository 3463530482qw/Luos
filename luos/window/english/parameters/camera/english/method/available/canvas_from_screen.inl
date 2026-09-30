namespace Gnik_luos {
    // 屏幕点(设备像素)→ 画布上的世界点,顺带把"夹在画布内"这件事做掉(画布外取最近边界)
    // 屏幕像素里那个灰边偏移由调用方先减掉(窗口层知道内接矩形从哪开始)
    Vector3 Camera::canvas_from_screen(double screen_x, double screen_y, double screen_width, double screen_height) const {
        const Canvas_rect canvas = canvas_rect();
        const Vector3 point = world_from_screen(screen_x, screen_y, screen_width, screen_height);
        return Vector3{
            std::min(std::max(point.x, canvas.min_x), canvas.max_x),
            std::min(std::max(point.y, canvas.min_y), canvas.max_y),
            canvas.z
        };
    }
}
