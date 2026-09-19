namespace Gnik_luos {
    void Vulkan_depth::create(vk::Extent2D extent) {
        // 先放上一张:视图引用图像,顺序反了等于让视图悬空
        view = nullptr;
        image = nullptr;
        memory = nullptr;

        if (extent.width == 0 || extent.height == 0) {
            return;
        }
        format = pick_format();

        vk::ImageCreateInfo image_info;
        image_info.setImageType(vk::ImageType::e2D);
        image_info.setFormat(format);
        image_info.setExtent(vk::Extent3D{extent.width, extent.height, 1});
        image_info.setMipLevels(1);
        image_info.setArrayLayers(1);
        image_info.setSamples(vk::SampleCountFlagBits::e1);
        image_info.setTiling(vk::ImageTiling::eOptimal);
        image_info.setUsage(vk::ImageUsageFlagBits::eDepthStencilAttachment);
        image_info.setSharingMode(vk::SharingMode::eExclusive);
        image_info.setInitialLayout(vk::ImageLayout::eUndefined);

        image = vk::raii::Image((*vulkan)->device, image_info);

        vk::MemoryRequirements requirement = image.getMemoryRequirements();
        vk::MemoryAllocateInfo allocate_info;
        allocate_info.setAllocationSize(requirement.size);
        allocate_info.setMemoryTypeIndex(find_memory_type(
            requirement.memoryTypeBits,
            vk::MemoryPropertyFlagBits::eDeviceLocal
        ));
        memory = vk::raii::DeviceMemory((*vulkan)->device, allocate_info);
        image.bindMemory(*memory, 0);

        // 深度图不带模板时只有深度那一面;带模板的格式(回退档)两面都要写进视图
        vk::ImageAspectFlags aspect = vk::ImageAspectFlagBits::eDepth;
        if (format == vk::Format::eD24UnormS8Uint) {
            aspect |= vk::ImageAspectFlagBits::eStencil;
        }

        vk::ImageViewCreateInfo view_info;
        view_info.setImage(*image);
        view_info.setViewType(vk::ImageViewType::e2D);
        view_info.setFormat(format);
        view_info.setSubresourceRange(vk::ImageSubresourceRange{}
            .setAspectMask(aspect)
            .setLevelCount(1)
            .setLayerCount(1));
        view = vk::raii::ImageView((*vulkan)->device, view_info);
    }
}
