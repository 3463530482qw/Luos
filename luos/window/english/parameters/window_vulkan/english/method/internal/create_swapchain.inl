namespace Gnik_luos {
    void Window_vulkan::create_swapchain(Vulkan& vulkan) {
        viewport.rebuild();
        swapchain.create(vulkan.physical_device, vulkan.device);
        swapchain.create_image_views(vulkan.device);
        renderpass.create(vulkan.device, swapchain.format);

        //render

        framebuffer.create(vulkan.device, renderpass.render_pass, swapchain.image_views, swapchain.extent);
        command_buffer.allocate(vulkan.device, command_pool.command_pool, static_cast<uint32_t>(swapchain.image_views.size()));
        synchronization.create(vulkan.device, static_cast<uint32_t>(swapchain.image_views.size()));
        record_command_buffers();
    }
}