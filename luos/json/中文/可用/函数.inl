void 添加(const std::string& json路径, const std::string& 名称) { add(json路径, 名称); }
void 清空() { clear(); }
void 删除(const std::string& 文件名) { remove(文件名); }
simdjson::dom::element 获取(const std::string& 文件名) { return get(文件名); }