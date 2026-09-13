namespace Gnik_luos {
    class Line_cmd_label {
        public:
        //放一块的是冲突项
            bool solid{true};
            bool dashed{false};

            bool gradient{}; 
            bool connected{true};   //相接的两段在拐角处是否连上(补外侧缺口;虚线时不补)
    };
}
