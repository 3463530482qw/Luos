namespace Gnik_luos {
    void Vulkan_texture::create_layout() {
        vk::DescriptorSetLayoutBinding binding;
        binding.setBinding(0);
        binding.setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
        binding.setDescriptorCount(1);
        binding.setStageFlags(vk::ShaderStageFlagBits::eFragment);

        vk::DescriptorSetLayoutCreateInfo layout_info;
        layout_info.setBindingCount(1);
        layout_info.setPBindings(&binding);
        descriptor_layout = vk::raii::DescriptorSetLayout(vulkan().device, layout_info);
    }
}
