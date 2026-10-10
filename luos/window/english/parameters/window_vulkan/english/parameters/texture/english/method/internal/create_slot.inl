namespace Gnik_luos {
    // 一张贴图:线性布局 + host visible,像素逐行按 rowPitch 拷进去(贴图尺寸不大,不值得为上传再拉一套命令缓冲)
    void Vulkan_texture::create_slot(Texture_slot& target, const unsigned char* pixels, uint32_t width, uint32_t height) {
        vk::FormatProperties properties = vulkan().physical_device.getFormatProperties(vk::Format::eR8G8B8A8Unorm);
        if ((properties.linearTilingFeatures & vk::FormatFeatureFlagBits::eSampledImage) == vk::FormatFeatureFlags{}) {
            throw std::runtime_error("Vulkan_texture::create_slot => R8G8B8A8_UNORM linear image cannot be sampled");
        }

        vk::ImageCreateInfo image_info;
        image_info.setImageType(vk::ImageType::e2D);
        image_info.setFormat(vk::Format::eR8G8B8A8Unorm);
        image_info.setExtent(vk::Extent3D{width, height, 1});
        image_info.setMipLevels(1);
        image_info.setArrayLayers(1);
        image_info.setSamples(vk::SampleCountFlagBits::e1);
        image_info.setTiling(vk::ImageTiling::eLinear);
        image_info.setUsage(vk::ImageUsageFlagBits::eSampled);
        image_info.setSharingMode(vk::SharingMode::eExclusive);
        image_info.setInitialLayout(vk::ImageLayout::eUndefined);
        target.image = vk::raii::Image(vulkan().device, image_info);

        vk::MemoryRequirements requirement = target.image.getMemoryRequirements();
        vk::MemoryAllocateInfo allocate_info;
        allocate_info.setAllocationSize(requirement.size);
        allocate_info.setMemoryTypeIndex(find_memory_type(
            requirement.memoryTypeBits,
            vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent
        ));
        target.memory = vk::raii::DeviceMemory(vulkan().device, allocate_info);
        target.image.bindMemory(*target.memory, 0);

        vk::SubresourceLayout image_layout = target.image.getSubresourceLayout(vk::ImageSubresource{vk::ImageAspectFlagBits::eColor, 0, 0});
        unsigned char* mapped = static_cast<unsigned char*>(target.memory.mapMemory(0, requirement.size));
        for (uint32_t row = 0; row < height; row++) {
            std::memcpy(
                mapped + image_layout.offset + static_cast<size_t>(row) * image_layout.rowPitch,
                pixels + static_cast<size_t>(row) * width * 4,
                static_cast<size_t>(width) * 4
            );
        }
        target.memory.unmapMemory();

        vk::ImageViewCreateInfo view_info;
        view_info.setImage(*target.image);
        view_info.setViewType(vk::ImageViewType::e2D);
        view_info.setFormat(vk::Format::eR8G8B8A8Unorm);
        view_info.setSubresourceRange(vk::ImageSubresourceRange{vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});
        target.view = vk::raii::ImageView(vulkan().device, view_info);

        vk::SamplerCreateInfo sampler_info;
        sampler_info.setMagFilter(vk::Filter::eLinear);
        sampler_info.setMinFilter(vk::Filter::eLinear);
        sampler_info.setMipmapMode(vk::SamplerMipmapMode::eNearest);
        sampler_info.setAddressModeU(vk::SamplerAddressMode::eRepeat);
        sampler_info.setAddressModeV(vk::SamplerAddressMode::eRepeat);
        sampler_info.setAddressModeW(vk::SamplerAddressMode::eRepeat);
        sampler_info.setMaxLod(0.0f);   // 只有一层
        target.sampler = vk::raii::Sampler(vulkan().device, sampler_info);

        vk::DescriptorPoolSize pool_size;
        pool_size.setType(vk::DescriptorType::eCombinedImageSampler);
        pool_size.setDescriptorCount(1);

        vk::DescriptorPoolCreateInfo pool_info;
        pool_info.setFlags(vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet);
        pool_info.setMaxSets(1);
        pool_info.setPoolSizeCount(1);
        pool_info.setPPoolSizes(&pool_size);
        target.pool = vk::raii::DescriptorPool(vulkan().device, pool_info);

        vk::DescriptorSetAllocateInfo set_info;
        set_info.setDescriptorPool(*target.pool);
        set_info.setDescriptorSetCount(1);
        set_info.setPSetLayouts(&*layout());
        std::vector<vk::raii::DescriptorSet> sets = vulkan().device.allocateDescriptorSets(set_info);
        target.descriptor = std::move(sets.front());

        vk::DescriptorImageInfo image_binding;
        image_binding.setSampler(*target.sampler);
        image_binding.setImageView(*target.view);
        image_binding.setImageLayout(vk::ImageLayout::eShaderReadOnlyOptimal);

        vk::WriteDescriptorSet write;
        write.setDstSet(*target.descriptor);
        write.setDstBinding(0);
        write.setDescriptorCount(1);
        write.setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
        write.setImageInfo(image_binding);
        vulkan().device.updateDescriptorSets(write, {});

        target.pending = true;   // 建出来还是 UNDEFINED 布局:第一次用之前要补屏障
    }
}
