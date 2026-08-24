namespace Gnik_luos {
    simdjson::dom::element Json::get(std::string_view name) {
        // 按名查找配置,找不到就报错
        auto it = data.find(name.data());
        if (it == data.end()) {
            throw std::runtime_error(std::string("Json::get => The configuration file doesn't exist: ") + name.data());
        }
        return it->second.root;
    }
}