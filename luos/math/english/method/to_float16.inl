namespace Gnik_luos {
    // 世界量交给 GPU 的唯一收窄点:推常量要的是 float[16]
    std::array<float, 16> to_float16(const Matrix4& matrix) {
        std::array<float, 16> packed{};
        for (int index = 0; index < 16; index++) {
            packed[static_cast<size_t>(index)] = static_cast<float>(matrix.m[index]);
        }
        return packed;
    }
}
