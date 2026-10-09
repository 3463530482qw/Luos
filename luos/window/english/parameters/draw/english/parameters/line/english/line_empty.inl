namespace Gnik_luos {
    bool line_empty(double length, double size_x, double size_y) {   // 退化线:没长度,或截面两个方向都没尺寸
        return length <= 0.0 || (size_x <= 0.0 && size_y <= 0.0);
    }
}
