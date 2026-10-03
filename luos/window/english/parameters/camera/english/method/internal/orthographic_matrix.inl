namespace Gnik_luos {
    // 正交档:取景框长在视图空间里,半宽/半高按画布尺寸与 zoom 算;
    // 视图空间 → NDC 是纯缩放平移,视图 z 越正越远,而 NDC 深度要 0 最近、1 最远,所以取负号
    // 纵向同样取负号:视图空间的 y 向上,NDC 的 y 向下,翻过来才与画布口径(x 右、y 上)一致
    Matrix4 Camera::private_orthographic_matrix() const {
        const double scale = (zoom > zoom_min) ? zoom : 1.0;
        const double half_width = canvas_width * 0.5 / scale;
        const double half_height = canvas_height * 0.5 / scale;
        if (half_width <= 0.0 || half_height <= 0.0) {
            return Matrix4{};
        }

        Matrix4 matrix;
        for (double& value : matrix.m) {
            value = 0.0;
        }
        matrix.m[0] = 1.0 / half_width;
        matrix.m[5] = -1.0 / half_height;
        matrix.m[10] = -1.0;
        matrix.m[15] = 1.0;
        return matrix;
    }
}
