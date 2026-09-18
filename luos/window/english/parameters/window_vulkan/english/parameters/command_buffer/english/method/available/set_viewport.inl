namespace Gnik_luos {
    void Vulkan_command_buffer::set_viewport(uint32_t index, vk::Rect2D viewport_area, vk::Rect2D scissor_area) {
        vk::Viewport viewport;
        viewport.setX(static_cast<float>(viewport_area.offset.x));
        viewport.setY(static_cast<float>(viewport_area.offset.y));
        viewport.setWidth(static_cast<float>(viewport_area.extent.width));
        viewport.setHeight(static_cast<float>(viewport_area.extent.height));
        viewport.setMinDepth(0.0f);
        viewport.setMaxDepth(1.0f);

        // 视口与裁剪当前取同一矩形(窗口内接矩形),两者语义分开:裁剪可独立于视口调整
        command_buffers[index].setViewport(0, viewport);
        command_buffers[index].setScissor(0, scissor_area);
    }
}
