namespace Gnik_luos {
    struct Line_span {               // 一条绘制命令在本帧顶点表里占的那一段,以及它要的贴图与展开尺寸
        std::string texture_path{};   // 空 = 不指定图片(走纯色贴图或顶点色)
        size_t begin{0};
        size_t count{0};
        double length{0.0};           // 展开图的宽(去重后各列宽之和):同一路径里取最长的那条命令来展开
        double size_x{0.0};           // 截面两个几何值:展开图的行高由它们拼
        double size_y{0.0};
        std::vector<double> column{};    // 展开图的列(去重后的段长):同长的段共用一列,贴图大小一致
    };
}
