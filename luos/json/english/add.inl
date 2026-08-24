namespace Gnik_luos {
    void Json::add(std::string_view json_path, std::string_view name) {
        auto [it, inserted] = data.try_emplace(name.data());
        simdjson::dom::element root;
        if (it->second.parser.load(json_path.data()).get(root)) {
            if (inserted) {
                data.erase(it);
            }
            throw std::runtime_error(std::string("Json::add => Failed to load the configuration file: ") + json_path.data());
        }
        it->second.root = root;
    }
}
