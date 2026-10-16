namespace Gnik_luos {
    // 视图空间的分量 → 世界的方向:就是相机的右/上/前三个基按分量组合
    // 传进来的 z 分量取"前方距离"(正数,与 view_matrix 同一口径);直线往返都不能改这个口径
    Vector3 Camera::private_view_direction(const Vector3& view_direction) const {
        const Rotation_basis basis = private_rotation_basis();
        return Vector3{
            basis.right.x * view_direction.x + basis.up.x * view_direction.y + basis.forward.x * view_direction.z,
            basis.right.y * view_direction.x + basis.up.y * view_direction.y + basis.forward.y * view_direction.z,
            basis.right.z * view_direction.x + basis.up.z * view_direction.y + basis.forward.z * view_direction.z
        };
    }
}
