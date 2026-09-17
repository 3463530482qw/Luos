namespace Gnik_luos {
    vk::Rect2D Window_vulkan::viewport_rect() {
        return vk::Rect2D{
            vk::Offset2D{viewport.cut_offset_width, viewport.cut_offset_height},
            vk::Extent2D{viewport.width, viewport.height}
        };
    }
}
