namespace Gnik_luos {
    void Json::add(const std::string& json_path, const std::string& name) {
        auto [it, inserted] = data.try_emplace(name);
        simdjson::dom::element root;
        if (it->second.parser.load(json_path).get(root)) {
            if (inserted) {
                data.erase(it);
            }
            throw std::runtime_error(std::string("Failed to load the configuration file: ") + json_path);
        }
        it->second.root = root;
    }
}
