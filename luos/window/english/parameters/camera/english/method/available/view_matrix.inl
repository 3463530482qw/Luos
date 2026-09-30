namespace Gnik_luos {
    // 世界 → 视图空间:矩阵的三行就是相机的右/上/后三个基(相机看向自己空间的 -z),
    // 平移项取基与"站位"的点积的相反数,所以不用真去求逆
    // 站位就是画布矩形的中心(private_view_origin):视图原点 = 画布中心,
    // 于是正交取景框与画布矩形对得上,反投影出来的点也正好落在矩形上
    // 视图空间口径:视图 x = 右,视图 y = 下,视图 z 越负越远
    Matrix4 Camera::view_matrix() const {
        const Rotation_basis basis = private_rotation_basis();
        const Vector3 back{-basis.forward.x, -basis.forward.y, -basis.forward.z};
        const Vector3 point = private_view_origin();

        Matrix4 matrix;
        matrix.m[0]  = basis.right.x;
        matrix.m[1]  = basis.up.x;
        matrix.m[2]  = back.x;
        matrix.m[3]  = 0.0;
        matrix.m[4]  = basis.right.y;
        matrix.m[5]  = basis.up.y;
        matrix.m[6]  = back.y;
        matrix.m[7]  = 0.0;
        matrix.m[8]  = basis.right.z;
        matrix.m[9]  = basis.up.z;
        matrix.m[10] = back.z;
        matrix.m[11] = 0.0;
        matrix.m[12] = -dot(basis.right, point);
        matrix.m[13] = -dot(basis.up, point);
        matrix.m[14] = -dot(back, point);
        matrix.m[15] = 1.0;
        return matrix;
    }
}
