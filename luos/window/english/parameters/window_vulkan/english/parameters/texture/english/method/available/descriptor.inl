namespace Gnik_luos {
    const vk::raii::DescriptorSet& Vulkan_texture::descriptor(const std::string& key, double block_width, double block_height, const Information_image* passed) {
        return take(key, block_width, block_height, passed).descriptor;
    }
}
