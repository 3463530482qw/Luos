std::unordered_map<std::string, HMODULE> private_data{};
simdjson::dom::object json_object{};
simdjson::dom::element config{};
std::string_view temporary_path{};