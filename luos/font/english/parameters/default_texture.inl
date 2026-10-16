namespace Gnik_luos {
    constexpr int font_default_texture_size = 64;   // 默认字形贴图的边长(像素,取 2 的幂)
    constexpr double font_default_texture_advance = 1.25;   // 没绑字体时每个字符按字号乘以这个数当方块宽(高度 = 字号)
    constexpr int font_default_texture_limit = 512;   // 贴图边长上限(取 2 的幂):字号再大也不无限往上加
}
