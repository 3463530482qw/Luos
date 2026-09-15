void init(Vulkan_info& vulkan_info);
void create_logical_device(uint32_t graphics_queue_family);
uint32_t find_memory_type(uint32_t type_filter, vk::MemoryPropertyFlags properties);   // 顶点缓冲等渲染资源分配用
