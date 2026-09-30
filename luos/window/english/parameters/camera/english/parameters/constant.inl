namespace Gnik_luos {
    // 相机模块内部共用的常量:数值只在这里出现一次,别处引用名字
    constexpr double pi = 3.14159265358979323846;   // 角度制换算用
    constexpr double zoom_min = 0.0001;             // 缩放下限:<= 0 会除零,统一夹到这里
    constexpr double near_min = 0.0001;             // 近平面下限:0 会让透视矩阵退化
    constexpr double aspect_fallback = 16.0 / 9.0;  // 画布尺寸无效时的兜底比例
}
