namespace Gnik_luos {
    // 屏幕点(设备像素,含灰边)→ 可见面上的世界点:
    //   正交档:就是画布上那一点(ray 与画布平面相交)
    //   透视档:射线打到地面(y = 0)的交点 —— 拾取地面上的东西用的就是它
    Vector3 Camera::world_from_screen(double screen_x, double screen_y, double screen_width, double screen_height) const {
        const World_ray ray = ray_through_screen(screen_x, screen_y, screen_width, screen_height);
        if (!is_perspective) {
            const Canvas_rect canvas = canvas_rect();
            const double distance = (ray.direction.z != 0.0) ? (canvas.z - ray.origin.z) / ray.direction.z : 0.0;
            return Vector3{
                ray.origin.x + ray.direction.x * distance,
                ray.origin.y + ray.direction.y * distance,
                canvas.z
            };
        }
        const Ground_hit hit = World::intersect_ground(ray);
        return hit.valid ? hit.point.position : Vector3{};
    }
}
