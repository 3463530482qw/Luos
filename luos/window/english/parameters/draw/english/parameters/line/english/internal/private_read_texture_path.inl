namespace Gnik_luos {
    void Line::private_read_texture_path(const simdjson::dom::element& source) {   // 只收字符串:用哪张图(空串 = 纯色那张)
        if (!source.get_string().get(temporary_text)) {
            texture_path = std::string(temporary_text);
        }
    }
}
