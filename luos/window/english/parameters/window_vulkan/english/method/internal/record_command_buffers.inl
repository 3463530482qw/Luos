namespace Gnik_luos {
    void Window_vulkan::record_command_buffers() {
        // 与移植前一致:清屏、裁剪、视口统一用同一个矩形(窗口内的内接矩形)
        // —— 内容只落在这块,四周余量保持清屏色(灰边),不随窗口比例被拉满
        vk::Rect2D area = viewport_rect();

        
    }
}