Texture_slot& take(const std::string& key, double block_width, double block_height, const Information_image* passed);
void create_layout();
void create_slot(Texture_slot& target, const unsigned char* pixels, uint32_t width, uint32_t height);
void create_block(const std::string& path, double block_width, double block_height);
bool block_stale(const std::string& path, double block_width, double block_height);
void read_blocks(const std::string& folder);
void write_blocks(const std::string& path);
uint32_t find_memory_type(uint32_t type_filter, vk::MemoryPropertyFlags properties);
