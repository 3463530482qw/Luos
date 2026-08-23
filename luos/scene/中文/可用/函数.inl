void 加载(const std::string& dll路径, const std::string& 函数名) { load(dll路径, 函数名); }
void 批量加载(const simdjson::dom::element& json, const std::string& 标签) { batch_load(json, 标签); }
Scene& 移除(const std::string& 名称) { return remove(名称); }
Scene& 清空() { return clear(); }
