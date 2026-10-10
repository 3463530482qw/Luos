namespace Gnik_luos {
    const vk::raii::DescriptorSet& Vulkan_texture::descriptor(const std::string& key, const std::vector<Line_span>& usage) {
        return take(key, usage).descriptor;
    }
}
