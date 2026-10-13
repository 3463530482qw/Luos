namespace Gnik_luos {
    struct Line_span {               // 一条绘制命令在本帧顶点表里占的那一段,以及它的贴图与几何
        std::string texture_key{};    // 贴图文件夹路径,或"image:<像素地址>:<宽>x<高>"(直接交的像素,所有块共用);空 = 走库内那张纯色
        size_t begin{0};
        size_t count{0};
        double size_x{0.0};           // 截面两个几何值:每段每面那些块的尺寸由它们与段长算
        double size_y{0.0};
        std::vector<double> segment{};   // 逐段长度(零长段不算),块的编号就按这个顺序
        std::vector<uint8_t> face_mask{};   // 逐段留下哪几个面:bit0 起端面 / bit1 终端面 / bit2..5 = +x/-x/+y/-y
        Information_image image{};       // 直接交的已加载像素(浅拷贝):命中"image:"键时所有块都用它
    };
}
