namespace Gnik_luos {
    void Line::private_read_texture(const simdjson::dom::element& source) {   // 取不到就保持原样
        if (!source.get_bool().get(temporary_flag)) {
            use_texture = temporary_flag;
        }
    }
}
