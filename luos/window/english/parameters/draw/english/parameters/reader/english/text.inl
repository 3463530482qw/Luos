namespace Gnik_luos {
    void read_text(const simdjson::dom::element& source, std::string& value) {   // 只收字符串:类型不对当没写
        std::string_view text{};
        if (!source.get_string().get(text)) {
            value = std::string(text);
        }
    }
}
