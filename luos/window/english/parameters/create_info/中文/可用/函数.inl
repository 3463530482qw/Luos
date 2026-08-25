Window_create_info& 批量加载(const simdjson::dom::element& json, std::string_view type) { return batch_load(json, type); };
void 内部加载() { private_load(); };