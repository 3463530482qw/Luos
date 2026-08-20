void add(const std::string& json_path, const std::string& name);
void clear();
void remove(const std::string& name);
const rapidjson::Document& get(const std::string& name);