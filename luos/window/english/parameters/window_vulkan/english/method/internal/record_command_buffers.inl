namespace Gnik_luos {
    void Window_vulkan::record_command_buffers() {
        // 与移植前一致:清屏、裁剪、视口统一用同一个矩形(窗口内的内接矩形)
        // —— 内容只落在这块,四周余量保持清屏色(灰边),不随窗口比例被拉满
        vk::Rect2D area = viewport_rect();
        // 深度每帧清成最远(1.0):先画的先落深度,后面的靠 LessOrEqual 比出来
        vk::ClearValue depth_clear{vk::ClearDepthStencilValue{1.0f, 0}};

        for (uint32_t index = 0; index < static_cast<uint32_t>(command_buffer.command_buffers.size()); index++) {
            command_buffer.begin(index);
            command_buffer.begin_render_pass(index, renderpass.render_pass, framebuffer.framebuffers[index], area, renderpass.clear_value, depth_clear);
            command_buffer.set_viewport(index, area, area);
            ground.draw(command_buffer.command_buffers[index]);   // 地面先铺,线条压在上面
            line_render.draw(command_buffer.command_buffers[index]);
            command_buffer.end(index);
        }
    }
}
