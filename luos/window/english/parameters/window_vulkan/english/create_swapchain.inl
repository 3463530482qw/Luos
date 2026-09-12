namespace Gnik_luos {
    void Window_vulkan::create_swapchain(
        uint32_t window_width,
        uint32_t window_height,
        float window_aspectratio,
        uint32_t logic_width
    ) {
        viewport.rebuild(window_width, window_height, window_aspectratio, logic_width);
        swapchain.create(vulkan->physical_device, vulkan->device, surface.surface, viewport.width, viewport.height);
        swapchain.create_image_views(vulkan->device);
        renderpass.create(vulkan->device, swapchain.format);
        framebuffer.create(vulkan->device, renderpass.render_pass, swapchain.image_views, swapchain.extent);
        command_buffer.allocate(vulkan->device, command_pool.command_pool, static_cast<uint32_t>(swapchain.image_views.size()));
        record_command_buffers();
    }
}
