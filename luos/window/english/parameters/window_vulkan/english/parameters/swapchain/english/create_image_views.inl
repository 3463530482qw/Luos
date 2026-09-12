namespace Gnik_luos {
    void Vulkan_swapchain::create_image_views(const vk::raii::Device& device) {
        image_views.clear();
        image_views.reserve(images.size());

        for (const auto& image : images) {
            vk::ImageViewCreateInfo create_info;
            create_info.setImage(image);
            create_info.setViewType(vk::ImageViewType::e2D);
            create_info.setFormat(format);
            create_info.setComponents({
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity
            });
            create_info.setSubresourceRange(vk::ImageSubresourceRange{
                vk::ImageAspectFlagBits::eColor,
                0, 1, 0, 1
            });

            image_views.emplace_back(device, create_info);
        }
    }
}
