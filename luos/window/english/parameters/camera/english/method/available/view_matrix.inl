namespace Gnik_luos {
    // 世界 → 视图空间:原点就是相机站位,视图 z = 前方距离(相机看向 -z,世界 z 越小的点越远)
    //   视图 x = 相机向右、视图 y = 相机向上、视图 z = 前方距离(前方为正,与投影矩阵的 w 同号)
    // forward 指向相机看的那一侧(世界 -z),"离相机多远"就是沿 forward 走多远,所以第三行取 forward 本身
    // 平移项取"该行基与站位的点积"的相反数,不用真去求逆
    Matrix4 Camera::view_matrix() const {
        const Rotation_basis basis = private_rotation_basis();
        const Vector3 point = position.position;

        Matrix4 matrix;
        matrix.m[0]  = basis.right.x;
        matrix.m[1]  = basis.up.x;
        matrix.m[2]  = basis.forward.x;
        matrix.m[3]  = 0.0;
        matrix.m[4]  = basis.right.y;
        matrix.m[5]  = basis.up.y;
        matrix.m[6]  = basis.forward.y;
        matrix.m[7]  = 0.0;
        matrix.m[8]  = basis.right.z;
        matrix.m[9]  = basis.up.z;
        matrix.m[10] = basis.forward.z;
        matrix.m[11] = 0.0;
        matrix.m[12] = -dot(basis.right, point);
        matrix.m[13] = -dot(basis.up, point);
        matrix.m[14] = -dot(basis.forward, point);
        matrix.m[15] = 1.0;
        return matrix;
    }
}
