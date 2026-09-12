namespace Gnik_luos {
    void Window_vulkan::initialize(
        Vulkan& vulkan_engine,
        SDL_Window* window,
        uint32_t window_width,
        uint32_t window_height,
        float window_aspectratio,
        uint32_t logic_width
    ) {
        if (initialized) {
            throw std::runtime_error("Window_vulkan::initialize => The window vulkan module has been initialized");
        }

        vulkan = &vulkan_engine;   // 借用:火山由应用持有与销毁,窗口不负责其生命周期
        surface.create(window, vulkan->instance);
        find_graphics_queue_family();
        vulkan->create_logical_device(graphics_queue_family);
        command_pool.create(vulkan->device, graphics_queue_family);
        synchronization.create(vulkan->device);

        pending_width = window_width;
        pending_height = window_height;
        pending_aspectratio = window_aspectratio;
        pending_logic_width = logic_width;
        initialized = true;

        // 窗口最小化时尺寸为 0,表面尚不可用:交换链留到尺寸恢复后由 rebuild 建立
        if (window_width == 0 || window_height == 0) {
            rebuild_flag = true;
            return;
        }

        create_swapchain(window_width, window_height, window_aspectratio, logic_width);
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

    Window_vulkan::~Window_vulkan() {
        // 显式销毁由 destroy 负责,这里只保证句柄与借用指针不残留
        initialized = false;
        rebuild_flag = false;
        vulkan = nullptr;
    }
}
