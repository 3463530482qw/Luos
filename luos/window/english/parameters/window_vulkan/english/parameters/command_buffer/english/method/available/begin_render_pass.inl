namespace Gnik_luos {
    void Vulkan_command_buffer::begin_render_pass(
        uint32_t index,
        const vk::raii::RenderPass& render_pass,
        const vk::raii::Framebuffer& framebuffer,
        vk::Rect2D& render_area,
        vk::ClearValue& clear_value,
        vk::ClearValue& depth_clear_value
    ) {
        // 清屏值按附件次序给:0 颜色、1 深度
        vk::ClearValue clear_values[]{clear_value, depth_clear_value};

        vk::RenderPassBeginInfo begin_info;
        begin_info.setRenderPass(*render_pass);
        begin_info.setFramebuffer(*framebuffer);
        begin_info.setRenderArea(render_area);
        begin_info.setClearValueCount(2);
        begin_info.setPClearValues(clear_values);

        command_buffers[index].beginRenderPass(begin_info, vk::SubpassContents::eInline);
    }
}
