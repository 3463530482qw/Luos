namespace Gnik_luos {
    // 视图空间的单位方向 → 世界的单位方向:就是相机的右/上/后三个基按分量组合
    Vector3 Camera::private_view_direction(const Vector3& view_direction) const {
        const Rotation_basis basis = private_rotation_basis();
        return Vector3{
            basis.right.x * view_direction.x + basis.up.x * view_direction.y - basis.forward.x * view_direction.z,
            basis.right.y * view_direction.x + basis.up.y * view_direction.y - basis.forward.y * view_direction.z,
            basis.right.z * view_direction.x + basis.up.z * view_direction.y - basis.forward.z * view_direction.z
        };
    }
}
