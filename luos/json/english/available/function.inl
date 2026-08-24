void add(std::string_view json_path, std::string_view name);
void clear();
void remove(std::string_view name);
simdjson::dom::element get(std::string_view name);