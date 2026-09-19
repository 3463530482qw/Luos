namespace Gnik_luos {
    void Vulkan_ground::draw(const vk::raii::CommandBuffer& command_buffer) {
        if (pipeline == nullptr || !enabled || camera == nullptr) {
            return;
        }
        command_buffer.bindPipeline(vk::PipelineBindPoint::eGraphics, *pipeline);
        command_buffer.pushConstants(
            *pipeline_layout,
            vk::ShaderStageFlagBits::eVertex | vk::ShaderStageFlagBits::eFragment,
            0,
            sizeof(push_constants),
            &push_constants
        );
        command_buffer.draw(6, 1, 0, 0);   // 六个顶点在顶点着色器里按 gl_VertexIndex 展开成地面四边形
    }
}
