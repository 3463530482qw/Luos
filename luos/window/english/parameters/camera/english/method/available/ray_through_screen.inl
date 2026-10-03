namespace Gnik_luos {
    // 屏幕点(设备像素,含窗口里的灰边)→ 世界射线
    //   正交档:可见范围就是画布矩形,你点的像素对应画布上的一点,射线从那个点朝视线方向发
    //   透视档:射线从**视图原点**(画布矩形中心,与 view_matrix 同一个点)出发,穿过那一点看远处
    // 两档都对齐 canvas_rect() 与 view_matrix():反投影出来的点必须能原样投影回同一个像素
    World_ray Camera::ray_through_screen(double screen_x, double screen_y, double screen_width, double screen_height) const {
        // 屏幕 → 裁剪空间:屏幕的 y 朝下,画布口径的世界 y 朝上(投影矩阵里已按这个取负号),
        // 所以 ndc.y 直接用屏幕比例的负向,两档都与投影保持一致
        const double width = (screen_width > 0.0) ? screen_width : 1.0;
        const double height = (screen_height > 0.0) ? screen_height : 1.0;
        const Vector3 ndc{
            screen_x / width * 2.0 - 1.0,
            screen_y / height * 2.0 - 1.0,
            0.0
        };
        const Canvas_rect canvas = canvas_rect();
        const double half_width = (canvas.max_x - canvas.min_x) * 0.5;
        const double half_height = (canvas.max_y - canvas.min_y) * 0.5;
        const Vector3 origin = private_view_origin();

        World_ray ray;
        if (!is_perspective) {
            // 正交:视图空间的 (x, y) 就是画布内的偏移,射线朝视线方向(视图空间 +z)
            const Vector3 view_point{ndc.x * half_width, -ndc.y * half_height, 0.0};
            const Vector3 offset = private_view_direction(view_point);
            ray.origin = Vector3{origin.x + offset.x, origin.y + offset.y, origin.z + offset.z};
            ray.direction = private_view_direction(Vector3{0.0, 0.0, 1.0});
            return ray;
        }

        // 透视:近平面是 z_view = near(视图空间越正越远,相机站位在 z 的负侧看向 +z)
        const double near_value = (near_plane > 0.0) ? near_plane : near_min;
        const double focal = std::tan(fov * 0.5 * pi / 180.0);
        const double aspect = (canvas.max_y > canvas.min_y)
            ? (canvas.max_x - canvas.min_x) / (canvas.max_y - canvas.min_y)
            : aspect_fallback;
        const Vector3 view_point{
            ndc.x * focal * aspect * near_value,
            -ndc.y * focal * near_value,
            near_value
        };
        Vector3 direction = private_view_direction(view_point);
        const double length = std::sqrt(
            direction.x * direction.x + direction.y * direction.y + direction.z * direction.z
        );
        if (length > 0.0) {
            direction.x /= length;
            direction.y /= length;
            direction.z /= length;
        }
        ray.origin = origin;   // 与 view_matrix 的平移项同一个点
        ray.direction = direction;
        return ray;
    }
}
