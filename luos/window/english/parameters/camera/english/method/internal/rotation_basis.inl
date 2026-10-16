namespace Gnik_luos {
    // 三个旋转(度)依次施加:先绕 x(俯仰)、再绕 y(偏航)、最后绕 z(翻滚),合出来的方向就是相机看的那个方向
    // 坐标系(右手系):x 正向右、y 正向上、z 正靠观察者;相机看向 -z,所以零旋转时 forward = (0, 0, -1)
    //   零旋转三个基就是世界轴:right = (1,0,0)、up = (0,1,0)、forward = (0,0,-1);right × up = -forward(右手系的相机约定)
    //   俯仰角 a > 0 = 抬头看上方:forward 的 y 分量随 a 变正,up 随之向后倒
    // 角度换算用的 pi 在 internal/constant.inl 里定义,全模块共用一份
    Rotation_basis Camera::private_rotation_basis() const {
        const double a = rotation_x * pi / 180.0;
        const double b = rotation_y * pi / 180.0;
        const double c = rotation_z * pi / 180.0;
        const double sa = std::sin(a), ca = std::cos(a);
        const double sb = std::sin(b), cb = std::cos(b);
        const double sc = std::sin(c), cc = std::cos(c);

        Rotation_basis basis;
        basis.right = {
            cc * cb,
            sc * cb,
            -sb
        };
        basis.up = {
            cc * sb * sa - sc * ca,
            sc * sb * sa + cc * ca,
            cb * sa
        };
        basis.forward = {
            sc * sa - cc * sb * ca,
            -cc * sa - sc * sb * ca,
            -cb * ca
        };
        return basis;
    }
}
