namespace Gnik_luos {
    void Window_vulkan::destroy_resources() {
        line_render.destroy();
        ground.destroy();
        synchronization.image_available_per_frame.clear();
        synchronization.render_finished_per_image.clear();
        synchronization.frame_fence.clear();
        command_buffer.command_buffers.clear();
        framebuffer.framebuffers.clear();
        depth.destroy();
        swapchain.reset();
        command_pool.command_pool.clear();
        renderpass.render_pass.clear();
        surface.surface.clear();
    }
}
