namespace Gnik_luos {
    // 世界 → 相机空间:矩阵的三行就是相机的右/上/后三个基(相机看向自己空间的 -z),
    // 平移项取基与相机位置的点积的相反数,所以不用真去求逆
    Matrix4 Camera::private_view_matrix() const {
        const Rotation_basis basis = private_rotation_basis();
        const std::array<float, 3> back{-basis.forward[0], -basis.forward[1], -basis.forward[2]};
        const std::array<float, 3> position{x, y, z};

        auto dot = [](const std::array<float, 3>& left, const std::array<float, 3>& right) {
            return left[0] * right[0] + left[1] * right[1] + left[2] * right[2];
        };

        Matrix4 matrix;
        matrix.m[0]  = basis.right[0];
        matrix.m[1]  = basis.up[0];
        matrix.m[2]  = back[0];
        matrix.m[3]  = 0.0f;
        matrix.m[4]  = basis.right[1];
        matrix.m[5]  = basis.up[1];
        matrix.m[6]  = back[1];
        matrix.m[7]  = 0.0f;
        matrix.m[8]  = basis.right[2];
        matrix.m[9]  = basis.up[2];
        matrix.m[10] = back[2];
        matrix.m[11] = 0.0f;
        matrix.m[12] = -dot(basis.right, position);
        matrix.m[13] = -dot(basis.up, position);
        matrix.m[14] = -dot(back, position);
        matrix.m[15] = 1.0f;
        return matrix;
    }
}
