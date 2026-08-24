void load(std::string_view dll_path, std::string_view function_name);
void batch_load(const simdjson::dom::element& json, std::string_view type);
Scene& remove(std::string_view name);
Scene& clear();