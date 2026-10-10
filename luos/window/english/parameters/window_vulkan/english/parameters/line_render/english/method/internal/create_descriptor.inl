namespace Gnik_luos {
    void Vulkan_line_render::create_descriptor() {
        vk::DescriptorSetLayoutBinding binding;
        binding.setBinding(0);
        binding.setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
        binding.setDescriptorCount(1);
        binding.setStageFlags(vk::ShaderStageFlagBits::eFragment);

        vk::DescriptorSetLayoutCreateInfo layout_info;
        layout_info.setBindingCount(1);
        layout_info.setPBindings(&binding);
        descriptor_layout = vk::raii::DescriptorSetLayout(vulkan().device, layout_info);

        vk::DescriptorPoolSize pool_size;
        pool_size.setType(vk::DescriptorType::eCombinedImageSampler);
        pool_size.setDescriptorCount(1);

        vk::DescriptorPoolCreateInfo pool_info;
        pool_info.setFlags(vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet);
        pool_info.setMaxSets(1);
        pool_info.setPoolSizeCount(1);
        pool_info.setPPoolSizes(&pool_size);
        descriptor_pool = vk::raii::DescriptorPool(vulkan().device, pool_info);

        vk::DescriptorSetAllocateInfo allocate_info;
        allocate_info.setDescriptorPool(*descriptor_pool);
        allocate_info.setDescriptorSetCount(1);
        allocate_info.setPSetLayouts(&*descriptor_layout);
        std::vector<vk::raii::DescriptorSet> sets = vulkan().device.allocateDescriptorSets(allocate_info);
        descriptor_set = std::move(sets.front());

        vk::DescriptorImageInfo image_info;
        image_info.setSampler(*texture_sampler);
        image_info.setImageView(*texture_view);
        image_info.setImageLayout(vk::ImageLayout::eShaderReadOnlyOptimal);

        vk::WriteDescriptorSet write;
        write.setDstSet(*descriptor_set);
        write.setDstBinding(0);
        write.setDescriptorCount(1);
        write.setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
        write.setImageInfo(image_info);
        vulkan().device.updateDescriptorSets(write, {});
    }
}
