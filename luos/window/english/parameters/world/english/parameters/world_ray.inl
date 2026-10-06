namespace Gnik_luos {
    struct World_ray {   // 世界空间里的一条射线:origin + 单位方向
        Vector3 origin{};
        Vector3 direction{0.0, 0.0, -1.0};
    };
}
