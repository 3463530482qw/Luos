namespace Gnik_luos {
    struct Matrix4 {   // 4x4 矩阵:列主序(m[列 * 4 + 行]),与线条推常量的 mvp[16] 同一口径
        float m[16]{
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    };
}
