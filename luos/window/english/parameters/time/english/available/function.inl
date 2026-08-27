void router();
void update();
Window_time& load();
Window_time& batch_load(const simdjson::dom::element& json, std::string_view type);