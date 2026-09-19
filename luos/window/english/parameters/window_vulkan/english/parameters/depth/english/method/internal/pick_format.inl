namespace Gnik_luos {
    vk::Format Vulkan_depth::pick_format() {
        // D32 最省事;个别驱动不给,就退到带模板的 D24S8(视图里那面模板跟着一起写)
        const std::array<vk::Format, 2> candidate{vk::Format::eD32Sfloat, vk::Format::eD24UnormS8Uint};
        for (vk::Format format_candidate : candidate) {
            vk::FormatProperties properties = (*vulkan)->physical_device.getFormatProperties(format_candidate);
            if ((properties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eDepthStencilAttachment) != vk::FormatFeatureFlags{}) {
                return format_candidate;
            }
        }
        throw std::runtime_error("Vulkan_depth::pick_format => No depth attachment format is supported");
    }
}
