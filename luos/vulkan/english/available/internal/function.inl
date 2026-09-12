void create_instance(Vulkan_info& vulkan_info);
bool create_debug_messenger(Vulkan_info& vulkan_info);
std::vector<vk::ValidationFeatureEnableEXT> collect_validation_features(const Vulkan_debug_info& debug_info);
uint32_t find_graphics_queue_family(vk::SurfaceKHR surface);
uint32_t find_memory_type(uint32_t type_filter, vk::MemoryPropertyFlags properties);
uint32_t rate_physical_device(const vk::raii::PhysicalDevice& rating_device);
void pick_physical_device();
