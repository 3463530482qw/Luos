namespace Gnik_luos {
    // 正交档:取景框长在视图空间里,半宽/半高按画布尺寸与 zoom 算;
    // 视图空间 → NDC 是纯缩放平移,深度 z 原样通到 NDC(0 最近、1 最远)
    // 默认取景(相机位置 (0,0,0)、无旋转、zoom = 1)时链路是恒等视图 × 这个缩放:
    //   世界 (0, 0) → NDC (-1, -1) = 画布左上角,即世界原点落在画布左下角(清单 5.4)
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
        matrix.m[5] = 1.0 / half_height;
        matrix.m[10] = 1.0;
        matrix.m[15] = 1.0;
        return matrix;
    }
}
