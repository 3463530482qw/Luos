namespace Gnik_luos {
    // 三个旋转(度)依次施加:先绕 x、再绕 y、最后绕 z,合出来的方向就是相机看的那个方向
    Rotation_basis Camera::private_rotation_basis() const {
        constexpr float pi = 3.14159265358979323846f;
        const float a = rotation_x * pi / 180.0f;
        const float b = rotation_y * pi / 180.0f;
        const float c = rotation_z * pi / 180.0f;
        const float sa = std::sin(a), ca = std::cos(a);
        const float sb = std::sin(b), cb = std::cos(b);
        const float sc = std::sin(c), cc = std::cos(c);

        Rotation_basis basis;
        basis.right = {cc * cb, sc * cb, -sb};
        basis.up = {cc * sb * sa - sc * ca, sc * sb * sa + cc * ca, cb * sa};
        basis.forward = {-(cc * sb * ca + sc * sa), -(sc * sb * ca - cc * sa), -(cb * ca)};
        return basis;
    }
}
