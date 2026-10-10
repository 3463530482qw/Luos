Image& load(const char* path);
Image& batch_load(const simdjson::dom::element& json, std::string_view type);
Information_image& find(const std::string& path);   // 按路径取像素:已在缓存里就直接给,不再解码
Image& save(const std::string& path, const unsigned char* pixels, uint32_t width, uint32_t height);   // RGBA8 写 PNG
Image& clear();
