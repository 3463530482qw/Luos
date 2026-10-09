namespace Gnik_luos {
    // 线段方向当局部 z:长度与截面坐标系(局部 x/y)在这一步落定,旋转不改它
    void Line::private_build_frame(size_t index) {   // 只按点序列里这一段的两个端点算
        const Vector3 start = private_point[index];
        const Vector3 end = private_point[index + 1];
        private_start = start;
        private_end = end;
        const Vector3 direction{end.x - start.x, end.y - start.y, end.z - start.z};
        private_length = std::sqrt(dot(direction, direction));
        private_axis = Vector3{0.0, 0.0, 1.0};
        private_side = Vector3{1.0, 0.0, 0.0};
        private_up = Vector3{0.0, 1.0, 0.0};
        if (private_length <= 0.0) {
            return;   // 退化线:方向无意义,截面留世界默认朝向,反正不出顶点
        }
        private_axis = normalize(direction);
        // 局部 x = 世界 z 叉乘线段方向:线躺在画布平面内时它就是画布平面内的法线,正是 size_x 量的那一边
        Vector3 reference{0.0, 0.0, 1.0};
        Vector3 side = cross(reference, private_axis);
        if (dot(side, side) <= 0.0) {
            reference = Vector3{0.0, 1.0, 0.0};   // 轴与世界 z 平行时叉积退化,改用世界 y 当参考
            side = cross(reference, private_axis);
        }
        private_side = normalize(side);
        private_up = cross(private_axis, private_side);
    }
}
