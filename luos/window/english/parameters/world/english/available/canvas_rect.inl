namespace Gnik_luos {
    struct Canvas_rect {   // 相机显示范围:世界空间里的一块矩形(默认在 z = 0 的画布平面上)
        double min_x{0.0}, min_y{0.0};
        double max_x{0.0}, max_y{0.0};
        double z{0.0};
    };
}
