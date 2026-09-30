namespace Gnik_luos {
    // 取景范围在当前朝向下覆盖到的世界矩形:相机没转时就是画布矩形本身,
    // 转过之后取画布矩形的四个角、按相机旋转摆到世界里再求 AABB(绘制侧只认轴对齐矩形)
    // 注意是"站位 + 旋转后的偏移",不是"相机位置 + 偏移":站位在画布中心(见 view_matrix)
    Rect Camera::rect() const {
        const Canvas_rect canvas = canvas_rect();
        const Rotation_basis basis = private_rotation_basis();
        const Vector3 origin = private_view_origin();

        // 旋转矩阵(纯方向):world = 站位 + R × 视图偏移
        Matrix4 rotation;
        rotation.m[0] = basis.right.x;
        rotation.m[1] = basis.right.y;
        rotation.m[2] = basis.right.z;
        rotation.m[4] = basis.up.x;
        rotation.m[5] = basis.up.y;
        rotation.m[6] = basis.up.z;
        rotation.m[8] = -basis.forward.x;
        rotation.m[9] = -basis.forward.y;
        rotation.m[10] = -basis.forward.z;

        // 画布在视图空间里的偏移:中心就是视图原点,xy 就是取景的半宽/半高
        const double half_width = (canvas.max_x - canvas.min_x) * 0.5;
        const double half_height = (canvas.max_y - canvas.min_y) * 0.5;
        const Vector4 corner[4]{
            {-half_width, -half_height, 0.0, 1.0},
            {half_width, -half_height, 0.0, 1.0},
            {half_width, half_height, 0.0, 1.0},
            {-half_width, half_height, 0.0, 1.0}
        };

        Rect box{};
        for (int index = 0; index < 4; index++) {
            const Vector4 offset = transform(rotation, corner[index]);
            const double x = origin.x + offset.x;
            const double y = origin.y + offset.y;
            if (index == 0) {
                box.left = x;
                box.right = x;
                box.top = y;
                box.bottom = y;
                continue;
            }
            box.left = std::min(box.left, x);
            box.right = std::max(box.right, x);
            box.top = std::min(box.top, y);
            box.bottom = std::max(box.bottom, y);
        }
        return box;
    }
}
