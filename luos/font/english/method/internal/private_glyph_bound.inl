namespace Gnik_luos {
    // 字体的字形上界(设计单位里最大的框):行宽按它定,免得到处重建图集;字体没给就用字号兜底
    int Font::private_glyph_bound(double scale) const {
        int x0 = 0;
        int y0 = 0;
        int x1 = 0;
        int y1 = 0;
        stbtt_GetFontBoundingBox(&font_info, &x0, &y0, &x1, &y1);
        int bound = std::max(std::max(std::abs(x0), std::abs(x1)), std::max(std::abs(y0), std::abs(y1)));
        bound = static_cast<int>(static_cast<double>(bound) * scale);
        return bound <= 0 ? 1 : bound;
    }
}
