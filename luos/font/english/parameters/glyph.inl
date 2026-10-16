namespace Gnik_luos {
    struct Glyph {                       // 一个字形:图集里的位置(uv 已按内缩半纹素留出采样余量)与在文字块里的偏移
        float u0{0.0f}, v0{0.0f}, u1{0.0f}, v1{0.0f};   // 图集 uv(归一化)
        float width{0.0f}, height{0.0f};                // 位图像素尺寸(烤制字号下的真实像素)
        float offset_x{0.0f}, offset_y{0.0f};           // 位图相对笔位/基线的偏移(像素)
        float advance{0.0f};                            // 水平前进量(像素)
    };
}
