namespace Gnik_luos {
    // 与相机同一口径:先绕 x、再绕 y、最后绕 z,三个角合出来的基就是旋转矩阵的三列;整根线当刚体转
    void Line::private_rotate() {
        const double a = rotation_x * degree_to_radian;
        const double b = rotation_y * degree_to_radian;
        const double c = rotation_z * degree_to_radian;
        const double sa = std::sin(a), ca = std::cos(a);
        const double sb = std::sin(b), cb = std::cos(b);
        const double sc = std::sin(c), cc = std::cos(c);
        private_basis_x = Vector3{cc * cb, sc * cb, -sb};
        private_basis_y = Vector3{cc * sb * sa - sc * ca, sc * sb * sa + cc * ca, cb * sa};
        private_basis_z = Vector3{cc * sb * ca + sc * sa, sc * sb * ca - cc * sa, cb * ca};

        const Vector3 pivot{rotation_point_x, rotation_point_y, rotation_point_z};
        private_start = private_rotate_vector(private_start, pivot);
        private_end = private_rotate_vector(private_end, pivot);
        const Vector3 origin{0.0, 0.0, 0.0};   // 截面朝向只转不平移
        private_side = private_rotate_vector(private_side, origin);
        private_up = private_rotate_vector(private_up, origin);
    }
}
