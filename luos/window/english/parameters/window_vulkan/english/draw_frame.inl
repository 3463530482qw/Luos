namespace Gnik_luos {
    void Window_vulkan::draw_frame() {
        if (!initialized) {
            return;
        }
        if (rebuild_flag) {
            // 窗口最小化时尺寸为 0,等恢复后再重建
            if (pending_width == 0 || pending_height == 0) {
                return;
            }
            try {
                rebuild();
            } catch (const vk::OutOfDateKHRError&) {
                return;   // 表面仍未就绪(最小化恢复瞬间),保持标记下帧重试
            } catch (const vk::SurfaceLostKHRError&) {
                return;
            }
        }

        synchronization.wait(vulkan->device);

        // 与移植前一致:命令缓冲每帧重录(带单次提交标记,不能复用上一次的录制结果)
        record_command_buffers();
        submit_frame();
    }
}
