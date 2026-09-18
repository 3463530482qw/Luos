namespace Gnik_luos {
    void Window_vulkan::create_swapchain(Vulkan& vulkan_engine) {
        viewport.rebuild();
        swapchain.create(vulkan_engine.physical_device, vulkan_engine.device);
        swapchain.create_image_views(vulkan_engine.device);
        renderpass.create(vulkan_engine.device, swapchain.format);

        // 线条渲染:渲染通道一换管线就得跟着重建,顶点缓冲只与设备有关(create 里自己留着)
        line_render.create(renderpass.render_pass, swapchain.extent);

        framebuffer.create(vulkan_engine.device, renderpass.render_pass, swapchain.image_views, swapchain.extent);
        command_buffer.allocate(vulkan_engine.device, command_pool.command_pool, static_cast<uint32_t>(swapchain.image_views.size()));
        synchronization.create(vulkan_engine.device, static_cast<uint32_t>(swapchain.image_views.size()));
        record_command_buffers();
    }
}
