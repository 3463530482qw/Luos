namespace Gnik_luos {
    void Window_vulkan::initialize(Vulkan& vulkan_engine) {
        if (initialized) {
            throw std::runtime_error("Window_vulkan::initialize => The window vulkan module has been initialized");
        }

        vulkan = &vulkan_engine;   // 借用:火山由应用持有与销毁,窗口火山不负责其生命周期
        surface.create(host->id, vulkan->instance);
        find_graphics_queue_family();
        vulkan->create_logical_device(graphics_queue_family);
        command_pool.create(vulkan->device, graphics_queue_family);

        pending_width = host->width;
        pending_height = host->height;
        pending_aspectratio = host->aspectratio;
        pending_logic_width = host->logic_width;
        initialized = true;

        // 窗口最小化时尺寸为 0,表面尚不可用:交换链留到尺寸恢复后由 rebuild 建立
        if (pending_width == 0 || pending_height == 0) {
            rebuild_flag = true;
            return;
        }

        create_swapchain(pending_width, pending_height, pending_aspectratio, pending_logic_width);
        rebuild_flag = false;
    }

    bool Window_vulkan::is_initialized() {
        return initialized;
    }

    void Window_vulkan::request_rebuild(uint32_t window_width, uint32_t window_height, float window_aspectratio) {
        pending_width = window_width;
        pending_height = window_height;
        if (window_aspectratio > 0.0f && std::isfinite(window_aspectratio)) {
            pending_aspectratio = window_aspectratio;
        }
        rebuild_flag = true;
    }
}
