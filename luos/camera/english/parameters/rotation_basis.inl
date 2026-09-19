namespace Gnik_luos {
    struct Rotation_basis {   // 相机的三个基向量(世界坐标):右、上、前;三个旋转都为 0 时就是看向 -z
        std::array<float, 3> right{1.0f, 0.0f, 0.0f};
        std::array<float, 3> up{0.0f, 1.0f, 0.0f};
        std::array<float, 3> forward{0.0f, 0.0f, -1.0f};
    };
}
