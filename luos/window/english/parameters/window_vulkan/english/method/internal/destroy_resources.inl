namespace Gnik_luos {
    void Window_vulkan::destroy_resources() {
        // 线条渲染的管线与顶点缓冲随 line_render 迁移接在此处
        synchronization.image_available_per_frame.clear();
        synchronization.render_finished_per_image.clear();
        synchronization.frame_fence.clear();
        command_buffer.command_buffers.clear();
        framebuffer.framebuffers.clear();
        swapchain.reset();
        command_pool.command_pool.clear();
        renderpass.render_pass.clear();
        surface.surface.clear();
    }
}
