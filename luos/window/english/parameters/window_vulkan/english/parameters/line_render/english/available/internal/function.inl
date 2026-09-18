std::vector<uint32_t> load_shader(const char* name);
void create_pipeline(const vk::raii::RenderPass& render_pass);
void create_vertex_buffer(size_t bytes);
uint32_t find_memory_type(uint32_t type_filter, vk::MemoryPropertyFlags properties);
