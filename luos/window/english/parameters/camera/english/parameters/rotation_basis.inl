namespace Gnik_luos {
    struct Rotation_basis {   // 相机的三个基向量(世界坐标):右、上、前;三个旋转都为 0 时就是看向 -z
        Vector3 right{1.0, 0.0, 0.0};
        Vector3 up{0.0, 1.0, 0.0};
        Vector3 forward{0.0, 0.0, -1.0};
    };
}
