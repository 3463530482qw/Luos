namespace Gnik_luos {
    // 只收字符串:用哪张图(空串 = 纯色那张)。**不动 use_texture** —— 走不走贴图由 texture 那个 bool 定,两个字段各管一件事
    void Line::private_read_texture_path(const simdjson::dom::element& source) {
        if (!source.get_string().get(temporary_text)) {
            texture_key = std::string(temporary_text);
            texture_image = Information_image{};
        }
    }
}
