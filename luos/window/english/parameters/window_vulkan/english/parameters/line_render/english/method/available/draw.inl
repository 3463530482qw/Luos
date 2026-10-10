namespace Gnik_luos {
    void Vulkan_line_render::draw(const vk::raii::CommandBuffer& command_buffer) {
        if (pipeline == nullptr || vertex_count == 0) {
            return;
        }
        command_buffer.bindPipeline(vk::PipelineBindPoint::eGraphics, *pipeline);
        command_buffer.bindVertexBuffers(0, {*vertex_buffer[vertex_frame]}, {0});
        for (size_t index = 0; index < group_range.size(); index++) {
            Line_push_constants group = push_constants;
            group.texture_scale_x = group_scale[index][0];   // 顶点里的 uv 是世界单位,按这一组的展开尺寸归一
            group.texture_scale_y = group_scale[index][1];
            command_buffer.pushConstants(*pipeline_layout, vk::ShaderStageFlagBits::eVertex, 0, sizeof(group), &group);
            texture().record_barrier(command_buffer, group_texture[index]);   // 这张图第一次用:补一条布局屏障
            command_buffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *pipeline_layout, 0, group_descriptor[index], {});
            command_buffer.draw(group_range[index][1], 1, group_range[index][0], 0);
        }
    }
}
