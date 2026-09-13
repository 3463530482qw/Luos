namespace Gnik_luos {
    struct Line_point {   // 链条上的一个点:位置 + "到这一点为止那一段"的颜色快照
        float x{0.0f}, y{0.0f};
        std::array<uint8_t, 2> r{255, 255};   // 两端红色分量(0~255)
        std::array<uint8_t, 2> g{255, 255};
        std::array<uint8_t, 2> b{255, 255};
        std::array<float, 2> a{1.0f, 1.0f};   // 两端透明度(0~1)
    };
}
