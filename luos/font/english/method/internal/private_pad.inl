namespace Gnik_luos {
    // 位图补成 2 的幂正方形,四边补透明:打包整齐、uv 好算,线性过滤也不会啃到相邻字形
    // 回 {左空隙, 上空隙, 右空隙, 下空隙};边长由 private_place 按 (位图 + 空隙) 取 2 的幂
    std::array<int, 4> Font::private_pad(int width, int height) {
        int side = 2;
        while (side < width + atlas_glyph_margin * 2 || side < height + atlas_glyph_margin * 2) {
            side *= 2;
        }
        const int left = (side - width) / 2;
        const int top = (side - height) / 2;
        return std::array<int, 4>{left, top, side - width - left, side - height - top};
    }
}
