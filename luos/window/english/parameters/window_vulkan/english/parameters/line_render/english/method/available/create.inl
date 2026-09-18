namespace Gnik_luos {
    void Vulkan_line_render::create(const vk::raii::RenderPass& render_pass, vk::Extent2D& swapchain_extent) {
        frame_extent = swapchain_extent;
        create_pipeline(render_pass);   // 渲染通道重建后管线必须跟着重建
        //if (vertex_buffer[0] == nullptr) {
            //create_vertex_buffer(vertex_buffer_bytes);
        //}
    }
}
