namespace Gnik_luos {
    // 正交档:取景框长在视图空间里,半宽/半高按画布尺寸与 zoom 算,xy 与相机距离无关;
    // 深度仍按近/远平面归一到 [0, 1](视图 z 就是前方距离:d = near → 0,d = far → 1),所以两档都能分前后
    // 纵向取负号:视图 y 向上,而裁剪空间的 y 朝下(Vulkan 口径),翻过来画布才对得上(x 右、y 上)
    Matrix4 Camera::private_orthographic_matrix() const {
        const double scale = (zoom > zoom_min) ? zoom : 1.0;
        const double half_width = canvas_width * 0.5 / scale;
        const double half_height = canvas_height * 0.5 / scale;
        if (half_width <= 0.0 || half_height <= 0.0) {
            return Matrix4{};
        }
        const double near_value = (near_plane > 0.0) ? near_plane : near_min;
        const double far_value = (far_plane > near_value) ? far_plane : near_value + 1.0;
        const double depth = far_value - near_value;

        Matrix4 matrix;
        for (double& value : matrix.m) {
            value = 0.0;
        }
        matrix.m[0] = 1.0 / half_width;
        matrix.m[5] = -1.0 / half_height;
        matrix.m[10] = 1.0 / depth;
        matrix.m[14] = -near_value / depth;
        matrix.m[15] = 1.0;
        return matrix;
    }
}
