namespace Gnik_luos {
    void Vulkan_renderpass::create(const vk::raii::Device& device, vk::Format format, vk::Format depth_format) {
        // 颜色附件:交换链图像,帧首清屏,帧尾交给交换链呈现
        vk::AttachmentDescription color_attachment;
        color_attachment.setFormat(format);
        color_attachment.setSamples(vk::SampleCountFlagBits::e1);
        color_attachment.setLoadOp(vk::AttachmentLoadOp::eClear);
        color_attachment.setStoreOp(vk::AttachmentStoreOp::eStore);
        color_attachment.setStencilLoadOp(vk::AttachmentLoadOp::eDontCare);
        color_attachment.setStencilStoreOp(vk::AttachmentStoreOp::eDontCare);
        color_attachment.setInitialLayout(vk::ImageLayout::eUndefined);
        color_attachment.setFinalLayout(vk::ImageLayout::ePresentSrcKHR);

        // 深度附件:只在帧内用,内容不必留到下一帧,所以初始布局 eUndefined(上一帧的深度直接丢)、
        // 结束布局停在附件最优(下一帧仍由 eUndefined 起,不用手工做布局转换)
        vk::AttachmentDescription depth_attachment;
        depth_attachment.setFormat(depth_format);
        depth_attachment.setSamples(vk::SampleCountFlagBits::e1);
        depth_attachment.setLoadOp(vk::AttachmentLoadOp::eClear);
        depth_attachment.setStoreOp(vk::AttachmentStoreOp::eDontCare);
        depth_attachment.setStencilLoadOp(vk::AttachmentLoadOp::eDontCare);
        depth_attachment.setStencilStoreOp(vk::AttachmentStoreOp::eDontCare);
        depth_attachment.setInitialLayout(vk::ImageLayout::eUndefined);
        depth_attachment.setFinalLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal);

        vk::AttachmentReference color_reference;
        color_reference.setAttachment(0);
        color_reference.setLayout(vk::ImageLayout::eColorAttachmentOptimal);

        vk::AttachmentReference depth_reference;
        depth_reference.setAttachment(1);
        depth_reference.setLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal);

        vk::SubpassDescription subpass;
        subpass.setPipelineBindPoint(vk::PipelineBindPoint::eGraphics);
        subpass.setColorAttachmentCount(1);
        subpass.setPColorAttachments(&color_reference);
        subpass.setPDepthStencilAttachment(&depth_reference);

        // 子通道依赖:外部(取像/呈现)完成后才允许写入颜色与深度附件
        vk::SubpassDependency dependency;
        dependency.setSrcSubpass(vk::SubpassExternal);
        dependency.setDstSubpass(0);
        dependency.setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests);
        dependency.setSrcAccessMask(vk::AccessFlagBits::eNone);
        dependency.setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests);
        dependency.setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite);

        const std::array<vk::AttachmentDescription, 2> attachments{color_attachment, depth_attachment};

        vk::RenderPassCreateInfo create_info;
        create_info.setAttachmentCount(static_cast<uint32_t>(attachments.size()));
        create_info.setPAttachments(attachments.data());
        create_info.setSubpassCount(1);
        create_info.setPSubpasses(&subpass);
        create_info.setDependencyCount(1);
        create_info.setPDependencies(&dependency);

        render_pass = vk::raii::RenderPass(device, create_info);
    }
}