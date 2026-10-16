namespace Gnik_luos {
    void read_flag(const simdjson::dom::element& source, bool& value) {   // 只收 bool:类型不对当没写
        bool flag = false;
        if (!source.get_bool().get(flag)) {
            value = flag;
        }
    }
}
