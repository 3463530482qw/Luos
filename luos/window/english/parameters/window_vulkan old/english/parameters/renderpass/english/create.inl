namespace Gnik_luos {
    void Vulkan_renderpass::create(const vk::raii::Device& device, vk::Format format) {
        // 唯一颜色附件:交换链图像,帧首清屏,帧尾交给交换链呈现
        vk::AttachmentDescription color_attachment;
        color_attachment.setFormat(format);
        color_attachment.setSamples(vk::SampleCountFlagBits::e1);
        color_attachment.setLoadOp(vk::AttachmentLoadOp::eClear);
        color_attachment.setStoreOp(vk::AttachmentStoreOp::eStore);
        color_attachment.setStencilLoadOp(vk::AttachmentLoadOp::eDontCare);
        color_attachment.setStencilStoreOp(vk::AttachmentStoreOp::eDontCare);
        color_attachment.setInitialLayout(vk::ImageLayout::eUndefined);
        color_attachment.setFinalLayout(vk::ImageLayout::ePresentSrcKHR);

        vk::AttachmentReference color_reference;
        color_reference.setAttachment(0);
        color_reference.setLayout(vk::ImageLayout::eColorAttachmentOptimal);

        vk::SubpassDescription subpass;
        subpass.setPipelineBindPoint(vk::PipelineBindPoint::eGraphics);
        subpass.setColorAttachmentCount(1);
        subpass.setPColorAttachments(&color_reference);

        // 子通道依赖:外部(取像/呈现)完成后才允许写入颜色附件
        vk::SubpassDependency dependency;
        dependency.setSrcSubpass(vk::SubpassExternal);
        dependency.setDstSubpass(0);
        dependency.setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
        dependency.setSrcAccessMask(vk::AccessFlagBits::eNone);
        dependency.setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
        dependency.setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite);

        vk::RenderPassCreateInfo create_info;
        create_info.setAttachmentCount(1);
        create_info.setPAttachments(&color_attachment);
        create_info.setSubpassCount(1);
        create_info.setPSubpasses(&subpass);
        create_info.setDependencyCount(1);
        create_info.setPDependencies(&dependency);

        render_pass = vk::raii::RenderPass(device, create_info);
    }
}
