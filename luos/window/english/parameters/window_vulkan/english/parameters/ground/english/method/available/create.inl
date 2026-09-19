namespace Gnik_luos {
    void Vulkan_ground::create(const vk::raii::RenderPass& render_pass) {
        create_pipeline(render_pass);   // 渲染通道一换管线就得跟着重建
    }
}
