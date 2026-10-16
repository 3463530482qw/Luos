namespace Gnik_luos {
    // 绕旋转中心转一个向量:先平移到以 pivot 为原点,乘旋转基,再移回去
    Vector3 Picture::private_rotate_vector(const Vector3& value, const Vector3& pivot) const {
        const Vector3 offset{value.x - pivot.x, value.y - pivot.y, value.z - pivot.z};
        return Vector3{
            pivot.x + private_basis_x.x * offset.x + private_basis_y.x * offset.y + private_basis_z.x * offset.z,
            pivot.y + private_basis_x.y * offset.x + private_basis_y.y * offset.y + private_basis_z.y * offset.z,
            pivot.z + private_basis_x.z * offset.x + private_basis_y.z * offset.y + private_basis_z.z * offset.z
        };
    }
}
