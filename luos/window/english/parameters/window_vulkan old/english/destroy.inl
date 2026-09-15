namespace Gnik_luos {
    void Window_vulkan::destroy_resources() {
        line_render.destroy();
        synchronization.image_available_per_frame.clear();
        synchronization.render_finished_per_image.clear();
        synchronization.frame_fence.clear();
        command_buffer.command_buffers.clear();
        framebuffer.framebuffers.clear();
        swapchain.reset();
        command_pool.command_pool.clear();
        renderpass.render_pass.clear();
        surface.destroy(vulkan->instance);
    }

    void Window_vulkan::destroy() {
        if (!initialized) {
            return;
        }
        initialized = false;

        vulkan->device.waitIdle();
        destroy_resources();
        vulkan = nullptr;   // 解绑借用,火山仍由应用持有
    }
}
