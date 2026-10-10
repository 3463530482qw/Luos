namespace Gnik_luos {
    void Line::private_read_texture(const simdjson::dom::element& source) {   // 只收 bool:走不走贴图
        if (!source.get_bool().get(temporary_flag)) {
            use_texture = temporary_flag;
        }
    }
}
