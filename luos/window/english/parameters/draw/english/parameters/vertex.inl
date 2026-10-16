namespace Gnik_luos {
    struct Vertex {                                // 通用顶点:对应线条着色器 inPosition/inUV/inColor/inTexture
        float x{0.0f}, y{0.0f};                    // 位置:世界坐标的 x/y(正交取景下 z = 0 平面),顶点缓冲是 GPU 格式所以收窄成 float
        float z{0.0f};                             // 世界 z:立体顶点带真实深度,压成几分深度由投影矩阵定
        float u{0.0f}, v{0.0f};                    // 纹理坐标:线条/图片是每块面自己的 0~1;文字是字形在图集里的区间(图集 v = 0 在位图顶行,与"世界 y 越往上越大"相反,给 uv 时要反着来)
        float r{1.0f}, g{1.0f}, b{1.0f}, a{1.0f};  // 颜色(0~1)
        float use_texture{0.0f};                   // 0 = 用上面的颜色,1 = 贴图 × 颜色(线/图/字都走这一档;字形覆盖率在图集 alpha 里)
    };
}
