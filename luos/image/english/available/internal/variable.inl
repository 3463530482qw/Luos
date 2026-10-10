simdjson::dom::object json_object{};
simdjson::dom::element config{};
std::string_view temporary_path{};
std::unordered_map<std::string, Information_image> cache{};   // 路径 → 像素:同一张图只解码一次,像素的释放归这里
