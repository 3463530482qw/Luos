namespace Gnik_luos {
    void Window_vulkan::rebuild() {
        vulkan->device.waitIdle();

        swapchain.reset();
        command_buffer.command_buffers.clear();
        framebuffer.framebuffers.clear();

        // 渲染通道与帧缓冲的格式/尺寸随交换链走,这里一并重建
        create_swapchain(*vulkan);

        rebuild_flag = false;
    }
}
