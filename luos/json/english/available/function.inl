void add(std::string json_path, std::string name);
void clear();
void remove(std::string name);
const rapidjson::Document& get(std::string name);