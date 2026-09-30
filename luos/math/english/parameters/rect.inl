namespace Gnik_luos {
    struct Rect {   // 世界坐标里的轴对齐矩形:相机可见范围与"外部填充"的边界都用它
        double left{0.0}, top{0.0}, right{0.0}, bottom{0.0};
    };
}
