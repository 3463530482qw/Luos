namespace Gnik_luos {
    // 一条绘制命令在本帧顶点表里占的那一段,以及它的贴图与几何
    struct Line_span {
        std::string texture_key{};    // 贴图键:块文件夹路径、单个图片文件路径,或"font:<字体>:<版本>:<身份>:<宽>x<高>";空 = 走库内那张纯色
        size_t begin{0};
        size_t count{0};
        double size_x{0.0};           // 截面两个几何值:每段每面那些块的尺寸由它们与段长算
        double size_y{0.0};
        std::vector<double> segment{};   // 逐段长度(零长段不算),块的编号就按这个顺序
        std::vector<uint8_t> face_mask{};   // 逐段留下哪几个面:bit0 起端面 / bit1 终端面 / bit2..5 = +x/-x/+y/-y
        bool single_image{false};        // true = 这一段是"一张图铺满":键就是那张图,顶点数按 count 走(图片与文字都是这一档)
        Information_image image{};       // 这张图的像素(按值拷进来):绘制命令这一帧末就被清掉,不能只留指针
    };
}
