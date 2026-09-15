namespace Gnik_luos {
    void Vulkan_line_render::draw(const vk::raii::CommandBuffer& command_buffer) {
        if (pipeline == nullptr || vertex_count == 0) {
            return;
        }
        command_buffer.bindPipeline(vk::PipelineBindPoint::eGraphics, *pipeline);
        command_buffer.pushConstants(*pipeline_layout, vk::ShaderStageFlagBits::eVertex, 0, sizeof(push_constants), &push_constants);
        command_buffer.bindVertexBuffers(0, {*vertex_buffer[vertex_frame]}, {0});
        command_buffer.draw(vertex_count, 1, 0, 0);
    }
}
