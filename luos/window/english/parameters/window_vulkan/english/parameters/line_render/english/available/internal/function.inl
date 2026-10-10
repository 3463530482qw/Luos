std::vector<uint32_t> load_shader(const char* name);
Vulkan_texture& texture();   // 贴图仓库:没接上就抛
void create_pipeline(const vk::raii::RenderPass& render_pass);
void create_vertex_buffer(size_t bytes);
uint32_t find_memory_type(uint32_t type_filter, vk::MemoryPropertyFlags properties);
