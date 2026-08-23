void load(const std::string& dll_path, const std::string& function_name);
void batch_load(const simdjson::dom::element& json, const std::string& type);
Scene& remove(const std::string& name);
Scene& clear();