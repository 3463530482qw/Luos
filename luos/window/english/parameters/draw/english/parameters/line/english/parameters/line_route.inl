    struct Line_route {   // 步骤表:按次序装配,private_run_route 顺着它跑;步数为 0 表示这条线不出顶点
        std::array<void (Line::*)(), 3> step{};
        size_t count{0};
    };

    inline bool line_empty(float length, float width) {   // 退化线:长度或线宽为 0,没有可铺的四边形
        return length <= 0.0f || width <= 0.0f;
    }
