namespace Gnik_luos {
    // 取一个 utf8 码位并前进指针:坏字节推进一步丢一个宽字符,不整行报废
    char32_t utf8_next(const char*& cursor) {
        const unsigned char lead = static_cast<unsigned char>(*cursor);
        if (lead < 0x80) {
            cursor++;
            return static_cast<char32_t>(lead);
        }
        size_t length = 1;
        char32_t value = static_cast<char32_t>(lead & 0x1F);
        if ((lead & 0xE0) == 0xC0) {
            length = 2;
            value = static_cast<char32_t>(lead & 0x1F);
        } else if ((lead & 0xF0) == 0xE0) {
            length = 3;
            value = static_cast<char32_t>(lead & 0x0F);
        } else if ((lead & 0xF8) == 0xF0) {
            length = 4;
            value = static_cast<char32_t>(lead & 0x07);
        }
        for (size_t index = 1; index < length; index++) {
            const unsigned char follow = static_cast<unsigned char>(cursor[index]);
            if ((follow & 0xC0) != 0x80) {
                cursor++;
                return static_cast<char32_t>(0xFFFD);
            }
            value = static_cast<char32_t>((value << 6) | (follow & 0x3F));   // 续字节只有低 6 位是数据
        }
        cursor += length;
        return value;
    }

    // 整串解成一行的码位:排版只按码位算,不逐字节猜
    std::u32string utf8_decode(const std::string& source) {
        std::u32string line{};
        line.reserve(source.size());
        const char* cursor = source.c_str();
        while (*cursor != '\0') {
            line.push_back(utf8_next(cursor));
        }
        return line;
    }
}
