namespace Gnik_luos {
    // 与相机、线条、图片同一口径:先绕 x、再绕 y、最后绕 z,三个角合出来的基就是旋转矩阵的三列
    void Text::private_rotate() {
        const double a = rotation_x * text_degree_to_radian;
        const double b = rotation_y * text_degree_to_radian;
        const double c = rotation_z * text_degree_to_radian;
        const double sa = std::sin(a), ca = std::cos(a);
        const double sb = std::sin(b), cb = std::cos(b);
        const double sc = std::sin(c), cc = std::cos(c);
        private_basis_x = Vector3{cc * cb, sc * cb, -sb};
        private_basis_y = Vector3{cc * sb * sa - sc * ca, sc * sb * sa + cc * ca, cb * sa};
        private_basis_z = Vector3{cc * sb * ca + sc * sa, sc * sb * ca - cc * sa, cb * ca};
    }

    // 绕旋转中心转一个点:先平移到以 pivot 为原点,乘旋转基,再移回去
    Vector3 Text::private_rotate_vector(const Vector3& value, const Vector3& pivot) const {
        const Vector3 offset{value.x - pivot.x, value.y - pivot.y, value.z - pivot.z};
        return Vector3{
            pivot.x + private_basis_x.x * offset.x + private_basis_y.x * offset.y + private_basis_z.x * offset.z,
            pivot.y + private_basis_x.y * offset.x + private_basis_y.y * offset.y + private_basis_z.y * offset.z,
            pivot.z + private_basis_x.z * offset.x + private_basis_y.z * offset.y + private_basis_z.z * offset.z
        };
    }
}
