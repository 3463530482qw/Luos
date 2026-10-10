namespace Gnik_luos {
    vk::raii::DescriptorSetLayout& Vulkan_texture::layout() {
        if (descriptor_layout == nullptr) {
            create_layout();
        }
        return descriptor_layout;
    }
}
