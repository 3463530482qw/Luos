namespace Gnik_luos {
    struct Ground_hit {   // 射线打到地面的结果:valid = false 时 point 无意义
        World_point point{};
        bool valid{false};
    };
}
