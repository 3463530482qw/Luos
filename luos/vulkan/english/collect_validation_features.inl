namespace Gnik_luos {
    // 头文件里的自由函数:inline 避免多编译单元重复定义
    inline std::vector<vk::ValidationFeatureEnableEXT> collect_validation_features(const Vulkan_debug_info& debug_info) {
        std::vector<vk::ValidationFeatureEnableEXT> features;
        if (debug_info.best_practices) {
            features.push_back(vk::ValidationFeatureEnableEXT::eBestPractices);
        }
        if (debug_info.synchronization_validation) {
            features.push_back(vk::ValidationFeatureEnableEXT::eSynchronizationValidation);
        }
        return features;
    }
}
