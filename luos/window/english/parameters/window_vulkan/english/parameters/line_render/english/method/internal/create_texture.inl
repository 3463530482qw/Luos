namespace Gnik_luos {
    // 线条贴图:一张 1×1 的纯色图,host visible 内存直接写,1×1 不值得走暂存缓冲
    void Vulkan_line_render::create_texture() {
        const uint8_t texel[4]{102, 102, 102, 255};   // 0.4 × 255;UNORM 采样出来就是 0.4

        // 1×1 的图直接写主机可见内存:必须走线性布局(optimal 布局的内存类型常常落在设备本地,拿不到 host visible)
        vk::FormatProperties properties = vulkan().physical_device.getFormatProperties(vk::Format::eR8G8B8A8Unorm);
        if ((properties.linearTilingFeatures & vk::FormatFeatureFlagBits::eSampledImage) == vk::FormatFeatureFlags{}) {
            throw std::runtime_error("Vulkan_line_render::create_texture => R8G8B8A8_UNORM linear image cannot be sampled");
        }

        vk::ImageCreateInfo image_info;
        image_info.setImageType(vk::ImageType::e2D);
        image_info.setFormat(vk::Format::eR8G8B8A8Unorm);
        image_info.setExtent(vk::Extent3D{1, 1, 1});
        image_info.setMipLevels(1);
        image_info.setArrayLayers(1);
        image_info.setSamples(vk::SampleCountFlagBits::e1);
        image_info.setTiling(vk::ImageTiling::eLinear);
        image_info.setUsage(vk::ImageUsageFlagBits::eSampled);
        image_info.setSharingMode(vk::SharingMode::eExclusive);
        image_info.setInitialLayout(vk::ImageLayout::eUndefined);
        texture_image = vk::raii::Image(vulkan().device, image_info);

        vk::MemoryRequirements requirement = texture_image.getMemoryRequirements();
        vk::MemoryAllocateInfo allocate_info;
        allocate_info.setAllocationSize(requirement.size);
        allocate_info.setMemoryTypeIndex(find_memory_type(
            requirement.memoryTypeBits,
            vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent
        ));
        texture_memory = vk::raii::DeviceMemory(vulkan().device, allocate_info);
        texture_image.bindMemory(*texture_memory, 0);

        void* mapped = texture_memory.mapMemory(0, sizeof(texel));
        std::memcpy(mapped, texel, sizeof(texel));
        texture_memory.unmapMemory();

        vk::ImageViewCreateInfo view_info;
        view_info.setImage(*texture_image);
        view_info.setViewType(vk::ImageViewType::e2D);
        view_info.setFormat(vk::Format::eR8G8B8A8Unorm);
        view_info.setSubresourceRange(vk::ImageSubresourceRange{vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});
        texture_view = vk::raii::ImageView(vulkan().device, view_info);

        vk::SamplerCreateInfo sampler_info;
        sampler_info.setMagFilter(vk::Filter::eNearest);
        sampler_info.setMinFilter(vk::Filter::eNearest);
        sampler_info.setMipmapMode(vk::SamplerMipmapMode::eNearest);
        sampler_info.setAddressModeU(vk::SamplerAddressMode::eClampToEdge);
        sampler_info.setAddressModeV(vk::SamplerAddressMode::eClampToEdge);
        sampler_info.setAddressModeW(vk::SamplerAddressMode::eClampToEdge);
        sampler_info.setMaxLod(0.0f);   // 只有一层
        texture_sampler = vk::raii::Sampler(vulkan().device, sampler_info);
    }
}
