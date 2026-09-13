namespace Gnik_luos {
    class Line_cmd_label {
        public:
        //放一块的是冲突项
            bool solid{true};
            bool dashed{false};

            bool gradient{}; 

            bool pixelated{false};  //按像素方块的颗粒重画几何(斜边与线宽都变成格子)

            bool connected{true};   //相接的两段在拐角处是否连上(补外侧缺口;虚线时不补)

            bool fill_inside{false};    //封边后填充形状内部

            bool fill_outside{false};   //填充相机画面里形状之外的区域

            bool fill_above{false};     //两样填充盖在线条之上(默认压在线条之下)

            //线条边缘怎么封(放一块的是冲突项):矩形是现在的做法,四种三角形按 封边大小 摆位
            bool edge_rect{true};    //端头平切,不封边

            bool edge_top{false};    //不回缩,三角形尖落在端头外 大小 处

            bool edge_middle{false}; //端头回缩 大小/2,尖落在原端头外 大小/2 处

            bool edge_bottom{false}; //端头回缩 大小,尖落在原端头

            bool edge_both{false};   //回缩 大小,一整块三角形高 2×大小
    };
}
