namespace Gnik_luos {
    bool line_empty(float length, float width) {   // 退化线:长度或线宽为 0,没有可铺的四边形
        return length <= 0.0f || width <= 0.0f;
    }
}