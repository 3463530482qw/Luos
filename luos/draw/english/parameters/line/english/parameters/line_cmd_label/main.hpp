namespace Gnik_luos {
    class Line_cmd_label {
        public:
            bool solid{true};

            bool dashed{false};

            bool gradient{}; 

            bool pixelated{false};  //按像素方块的颗粒重画几何(斜边与线宽都变成格子)

            bool connected{true};   //相接的两段在拐角处是否连上(补外侧缺口;虚线时不补)

            bool fill_inside{false};    //封边后填充形状内部

            bool fill_outside{false};   //填充相机画面里形状之外的区域

            bool fill_above{false};     //两样填充盖在线条之上(默认压在线条之下)

            //线条边缘怎么封(放一块的是冲突项):四种三角形只差延伸点落在哪,两种半圆是圆头的正负形
            bool edge_rect{true};    //端头平切,不封边

            bool edge_top{false};    //回缩 大小/2,延伸点在线宽上沿、原端头外 大小/2

            bool edge_middle{false}; //同回缩,延伸点落在线宽中线

            bool edge_bottom{false}; //同回缩,延伸点在线宽下沿

            bool edge_both{false};   //负形:端面挖掉一个三角形,上下两块尖一直留到原端头

            bool edge_round{false};        //半圆正形:端头鼓出一个半圆(直径 = 封边大小)

            bool edge_round_notch{false};  //半圆负形:端面挖进一个半圆(直径 = 封边大小)
    };
}
