namespace Gnik_luos {
    void Window_vulkan::record_command_buffers() {
        // 与移植前一致:清屏、裁剪、视口统一用同一个矩形(窗口内的内接矩形)
        // —— 内容只落在这块,四周余量保持清屏色(灰边),不随窗口比例被拉满
        vk::Rect2D area = viewport_rect();

        for (uint32_t index = 0; index < static_cast<uint32_t>(command_buffer.command_buffers.size()); index++) {
            command_buffer.begin(index);
            command_buffer.begin_render_pass(index, renderpass.render_pass, framebuffer.framebuffers[index], area, renderpass.clear_value);
            command_buffer.set_viewport(index, area, area);
            // 绘制命令由此处录制,线条随 line_render 迁移接在 set_viewport 之后
            command_buffer.end(index);
        }
    }
}
