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
        record_command_buffers();
        submit_frame();
    }
}
