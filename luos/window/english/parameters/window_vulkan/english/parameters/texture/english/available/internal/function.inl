Texture_slot& take(const std::string& path, const std::vector<Line_span>& usage);
void create_layout();
void create_slot(Texture_slot& target, const unsigned char* pixels, uint32_t width, uint32_t height);
void create_guide(const std::string& path, const std::vector<Line_span>& usage);
uint32_t find_memory_type(uint32_t type_filter, vk::MemoryPropertyFlags properties);
