namespace Gnik_luos {
    // 三个旋转(度)依次施加:先绕 x、再绕 y、最后绕 z,合出来的方向就是相机看的那个方向
    // 角度换算用的 pi 在 internal/constant.inl 里定义,全模块共用一份
    Rotation_basis Camera::private_rotation_basis() const {
        const double a = rotation_x * pi / 180.0;
        const double b = rotation_y * pi / 180.0;
        const double c = rotation_z * pi / 180.0;
        const double sa = std::sin(a), ca = std::cos(a);
        const double sb = std::sin(b), cb = std::cos(b);
        const double sc = std::sin(c), cc = std::cos(c);

        Rotation_basis basis;
        basis.right = {cc * cb, sc * cb, -sb};
        basis.up = {cc * sb * sa - sc * ca, sc * sb * sa + cc * ca, cb * sa};
        // 零旋转看向 +z(画布口径:x 向右、y 向上、z 向前,世界量与屏幕都同向)
        basis.forward = {cc * sb * ca + sc * sa, sc * sb * ca - cc * sa, cb * ca};
        return basis;
    }
}
