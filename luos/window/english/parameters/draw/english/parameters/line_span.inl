namespace Gnik_luos {
    struct Line_span {               // 一条绘制命令在本帧顶点表里占的那一段,以及它要的贴图与展开尺寸
        std::string texture_key{};    // 贴图槽位键:文件路径或"image:<像素地址>";空 = 走纯色贴图或顶点色
        size_t begin{0};
        size_t count{0};
        double length{0.0};           // 展开图的宽(各列宽之和):同一路径里取最长的那条命令来展开
        double size_x{0.0};           // 截面两个几何值:展开图的行高由它们拼
        double size_y{0.0};
        std::vector<double> column{};    // 展开图的列(逐段长度):列数跟段数一致,同长的段列宽相等
        Information_image image{};       // 直接给的已加载像素(浅拷贝):命中"image:"键时拿它建槽位
    };
}
