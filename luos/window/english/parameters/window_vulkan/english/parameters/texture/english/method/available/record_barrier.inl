namespace Gnik_luos {
    void Vulkan_texture::record_barrier(const vk::raii::CommandBuffer& command_buffer, const std::string& key) {
        auto it = slot.find(key);
        if (it == slot.end() || !it->second.pending) {
            return;   // 没用过这张图,或者布局早就换好了
        }
        vk::ImageMemoryBarrier barrier;
        barrier.setOldLayout(vk::ImageLayout::eUndefined);
        barrier.setNewLayout(vk::ImageLayout::eShaderReadOnlyOptimal);
        barrier.setSrcQueueFamilyIndex(vk::QueueFamilyIgnored);
        barrier.setDstQueueFamilyIndex(vk::QueueFamilyIgnored);
        barrier.setImage(*it->second.image);
        barrier.setSubresourceRange(vk::ImageSubresourceRange{vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});
        barrier.setSrcAccessMask(vk::AccessFlagBits::eHostWrite);
        barrier.setDstAccessMask(vk::AccessFlagBits::eShaderRead);
        command_buffer.pipelineBarrier(vk::PipelineStageFlagBits::eHost, vk::PipelineStageFlagBits::eFragmentShader, {}, {}, {}, barrier);
        it->second.pending = false;   // 布局跟着图走,后面的帧不用再记
    }
}
