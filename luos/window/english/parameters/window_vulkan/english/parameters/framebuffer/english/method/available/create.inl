namespace Gnik_luos {
    void Vulkan_framebuffer::create(
        const vk::raii::Device& device,
        const vk::raii::RenderPass& render_pass,
        const std::vector<vk::raii::ImageView>& image_views,
        const vk::raii::ImageView& depth_view,
        vk::Extent2D extent
    ) {
        framebuffers.clear();
        framebuffers.reserve(image_views.size());

        // 帧缓冲把渲染通道的附件约定与具体图像视图绑定起来,每张交换链图像一个;
        // 附件次序须与渲染通道一致:0 颜色(交换链图像)、1 深度(所有帧缓冲共用同一张深度图)
        for (const auto& image_view : image_views) {
            vk::ImageView attachments[]{*image_view, *depth_view};

            vk::FramebufferCreateInfo create_info;
            create_info.setRenderPass(*render_pass);
            create_info.setAttachmentCount(2);
            create_info.setPAttachments(attachments);
            create_info.setWidth(extent.width);
            create_info.setHeight(extent.height);
            create_info.setLayers(1);

            framebuffers.emplace_back(device, create_info);
        }
    }
}
