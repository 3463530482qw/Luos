namespace Gnik_luos {
    void Vulkan_command_buffer::begin(uint32_t index) {
        // 每帧重录,单次提交标记正合适;若将来改为跨帧复用,这里要换成 eSimultaneousUse
        vk::CommandBufferBeginInfo begin_info;
        begin_info.setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

        command_buffers[index].begin(begin_info);
    }
}
