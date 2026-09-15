namespace Gnik_luos {
    uint32_t Vulkan::rate_physical_device(const vk::raii::PhysicalDevice& rating_device) {
        auto properties = rating_device.getProperties();
        auto features = rating_device.getFeatures();

        uint32_t score = 0;
        if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
            score += 150;
        }
        score += properties.limits.maxImageDimension2D / 256;
        if (features.geometryShader) {
            score += 50;
        }
        if (features.samplerAnisotropy) {
            score += 30;
        }
        return score;
    }
}
