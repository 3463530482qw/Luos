namespace Gnik_luos {
    void Json::add(std::string json_path, std::string name) {
        std::ifstream file(json_path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error(std::string("Failed to load the configuration file: ") + json_path);
        }
        rapidjson::IStreamWrapper stream(file, buffer.data(), buffer.size());
        rapidjson::Document document;
         document.ParseStream(stream);
        if (document.HasParseError()) {
            throw std::runtime_error(std::string("Failed to load the configuration file: ") + json_path);
        }
        data.insert_or_assign(std::move(name), std::move(document));
    }
}