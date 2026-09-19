namespace Gnik_luos {
    // 正交(2D 档):世界 xy 就是画布像素,画面以相机位置为中心、按 zoom 缩放;
    // z 原样通到 NDC 深度(0 最近、1 最远),与加相机之前线条渲染自己拼的那个矩阵逐项一致
    Matrix4 Camera::private_orthographic_matrix() const {
        const float scale = (zoom > 0.0f) ? zoom : 1.0f;
        const float half_width = canvas_width * 0.5f / scale;
        const float half_height = canvas_height * 0.5f / scale;
        if (half_width <= 0.0f || half_height <= 0.0f) {
            return Matrix4{};
        }

        Matrix4 matrix;
        for (float& value : matrix.m) {
            value = 0.0f;
        }
        matrix.m[0] = 1.0f / half_width;
        matrix.m[5] = 1.0f / half_height;
        matrix.m[10] = 1.0f;
        matrix.m[12] = -x / half_width;
        matrix.m[13] = -y / half_height;
        matrix.m[15] = 1.0f;
        return matrix;
    }
}
