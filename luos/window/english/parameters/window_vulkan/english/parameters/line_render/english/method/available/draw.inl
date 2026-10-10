namespace Gnik_luos {
    void Vulkan_line_render::draw(const vk::raii::CommandBuffer& command_buffer) {
        if (pipeline == nullptr || vertex_count == 0) {
            return;
        }
        if (!texture_ready) {
            // 贴图刚建出来还是 UNDEFINED 布局:第一次用它之前记一条屏障,顺带把主机写入变成对片元可见
            vk::ImageMemoryBarrier barrier;
            barrier.setOldLayout(vk::ImageLayout::eUndefined);
            barrier.setNewLayout(vk::ImageLayout::eShaderReadOnlyOptimal);
            barrier.setSrcQueueFamilyIndex(vk::QueueFamilyIgnored);
            barrier.setDstQueueFamilyIndex(vk::QueueFamilyIgnored);
            barrier.setImage(*texture_image);
            barrier.setSubresourceRange(vk::ImageSubresourceRange{vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});
            barrier.setSrcAccessMask(vk::AccessFlagBits::eHostWrite);
            barrier.setDstAccessMask(vk::AccessFlagBits::eShaderRead);
            command_buffer.pipelineBarrier(vk::PipelineStageFlagBits::eHost, vk::PipelineStageFlagBits::eFragmentShader, {}, {}, {}, barrier);
            texture_ready = true;   // 布局跟着图走,后面的帧不用再记
        }
        command_buffer.bindPipeline(vk::PipelineBindPoint::eGraphics, *pipeline);
        command_buffer.pushConstants(*pipeline_layout, vk::ShaderStageFlagBits::eVertex, 0, sizeof(push_constants), &push_constants);
        command_buffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *pipeline_layout, 0, *descriptor_set, {});
        command_buffer.bindVertexBuffers(0, {*vertex_buffer[vertex_frame]}, {0});
        command_buffer.draw(vertex_count, 1, 0, 0);
    }
}
