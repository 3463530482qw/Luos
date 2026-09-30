namespace Gnik_luos {
    void Window_vulkan::rebuild() {
        Vulkan& engine = vulkan_engine();
        engine.device.waitIdle();

        // 尺寸/比例都从宿主窗口现取:窗口缩放后这一帧就能用上新视口
        update_viewport();

        swapchain.reset();
        command_buffer.command_buffers.clear();
        framebuffer.framebuffers.clear();

        // 渲染通道与帧缓冲的格式/尺寸随交换链走,这里一并重建
        create_swapchain(engine);

        rebuild_flag = false;
    }
}
