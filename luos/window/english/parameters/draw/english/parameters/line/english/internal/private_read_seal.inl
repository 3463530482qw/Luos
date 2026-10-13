namespace Gnik_luos {
    void Line::private_read_seal(const simdjson::dom::element& source) {   // 只收 bool:封不封边
        if (!source.get_bool().get(temporary_flag)) {
            use_seal = temporary_flag;
        }
    }
}
