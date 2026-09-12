namespace Gnik_luos {
    void Vulkan_command_buffer::begin_render_pass(
        uint32_t index,
        const vk::raii::RenderPass& render_pass,
        const vk::raii::Framebuffer& framebuffer,
        vk::Rect2D render_area,
        vk::ClearValue clear_value
    ) {
        vk::RenderPassBeginInfo begin_info;
        begin_info.setRenderPass(*render_pass);
        begin_info.setFramebuffer(*framebuffer);
        begin_info.setRenderArea(render_area);
        begin_info.setClearValueCount(1);
        begin_info.setPClearValues(&clear_value);

        command_buffers[index].beginRenderPass(begin_info, vk::SubpassContents::eInline);
    }
}
