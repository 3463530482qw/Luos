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
    };
}
