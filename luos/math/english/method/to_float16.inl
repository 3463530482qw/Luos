namespace Gnik_luos {
    // 世界量交给 GPU 的唯一收窄点:推常量要的是 float[16]
    // Matrix4 是列主序(m[列 * 4 + 行]),GLSL 的 mat4 也按列主序读(每 4 个 float 一列),
    // 两者一致,所以原样按 index 拷进去即可:平移落在 mvp[12..15],w 行落在 mvp[3]/[7]/[11]/[15]
    std::array<float, 16> to_float16(const Matrix4& matrix) {
        std::array<float, 16> packed{};
        for (int index = 0; index < 16; index++) {
            packed[static_cast<size_t>(index)] = static_cast<float>(matrix.m[index]);
        }
        return packed;
    }
}
