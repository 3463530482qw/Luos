namespace Gnik_luos {
    const vk::raii::DescriptorSet& Vulkan_texture::descriptor(const std::string& path, const std::vector<Line_span>& usage) {
        return take(path, usage).descriptor;
    }
}
