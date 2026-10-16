namespace Gnik_luos {
    // 逐行逐字排:文字块左上角定第一行基线,行高往下推,每行按对齐挪一个身位
    // 绑了字体就取字形,没绑就按字号排方块(默认字形贴图铺满每个方块)
    void Text::private_layout() {
        const double pixel_height = static_cast<double>(font_size);
        const double step = line_height > 0.0f
            ? static_cast<double>(line_height)
            : (face == nullptr ? pixel_height : face->line_height(pixel_height));
        double baseline = static_cast<double>(y1) + (face == nullptr ? pixel_height : face->ascent(pixel_height));
        const bool placeholder = face == nullptr;
        const float box_width = font_size * static_cast<float>(font_default_texture_advance);
        const float box_height = font_size;   // 方块高 = 字号
        size_t begin = 0;
        while (begin <= content.size()) {
            const size_t end = content.find_first_of("\r\n", begin);
            const std::u32string line = utf8_decode(content.substr(begin, end == std::string::npos ? std::string::npos : end - begin));
            const float line_width = private_measure(line);
            float pen_x = x1 + private_align_offset(line_width);
            for (char32_t codepoint : line) {
                if (placeholder) {
                    private_emit(Glyph{}, pen_x, static_cast<float>(baseline), true, box_width, box_height);
                } else {
                    private_emit(face->glyph(codepoint, pixel_height), pen_x, static_cast<float>(baseline), false, 0.0f, 0.0f);
                }
                pen_x += private_advance(codepoint) + letter_spacing;
            }
            if (end == std::string::npos) {
                break;
            }
            begin = content.find_first_not_of("\r\n", end);
            if (begin == std::string::npos) {
                break;
            }
            baseline += step;
        }
    }
}
