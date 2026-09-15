void create_instance(Vulkan_info& vulkan_info);
bool create_debug_messenger(Vulkan_info& vulkan_info);
std::vector<vk::ValidationFeatureEnableEXT> collect_validation_features(const Vulkan_debug_info& debug_info);