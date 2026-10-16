namespace Gnik_luos {
    // \n 断出来的行数:空文字也算一行(不出顶点,但行数不假)
    int Text::private_line_count() const {
        int count = 1;
        for (char character : content) {
            if (character == '\n') {
                count++;
            }
        }
        return count;
    }

    // 一个码位的前进量:绑了字体取字形的,没绑就按"字号 × 默认字宽比"推一个方块
    float Text::private_advance(char32_t codepoint) const {
        if (face == nullptr) {
            return font_size * static_cast<float>(font_default_texture_advance);
        }
        return face->glyph(codepoint, static_cast<double>(font_size)).advance;
    }

    // 一行的排版宽度:逐码位取前进量累加,每个字形后面再加一份字距
    float Text::private_measure(const std::u32string& line) const {
        double width = 0.0;
        for (char32_t codepoint : line) {
            width += static_cast<double>(private_advance(codepoint)) + static_cast<double>(letter_spacing);
        }
        return static_cast<float>(width);
    }
}
