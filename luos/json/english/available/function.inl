void add(const std::string& json_path, const std::string& name);
void clear();
void remove(const std::string& name);
simdjson::dom::element get(const std::string& name);