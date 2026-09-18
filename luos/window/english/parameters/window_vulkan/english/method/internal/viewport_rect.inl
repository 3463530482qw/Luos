namespace Gnik_luos {
    vk::Rect2D Window_vulkan::viewport_rect() {
        // 视口是按窗口尺寸算出来的"想要"的矩形,帧缓冲却按交换链实际 extent 建:
        // 拖边框时表面会把交换链夹回当前窗口尺寸(甚至夹到上一步),两者就会错开。
        // 这里取交集,保证 renderArea 永远落在帧缓冲内 —— 否则校验层报
        // VUID-VkRenderPassBeginInfo-pNext-02852/02853,有的驱动接着就丢设备。
        int32_t x = std::clamp(viewport.cut_offset_width, 0, static_cast<int32_t>(swapchain.extent.width));
        int32_t y = std::clamp(viewport.cut_offset_height, 0, static_cast<int32_t>(swapchain.extent.height));
        uint32_t width = std::min(viewport.width, swapchain.extent.width - static_cast<uint32_t>(x));
        uint32_t height = std::min(viewport.height, swapchain.extent.height - static_cast<uint32_t>(y));
        return vk::Rect2D{vk::Offset2D{x, y}, vk::Extent2D{width, height}};
    }
}
