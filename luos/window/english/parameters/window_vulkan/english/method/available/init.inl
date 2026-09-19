namespace Gnik_luos {
    void Window_vulkan::init(Vulkan& vulkan_engine) {
        if (initialized) {
            throw std::runtime_error("Window_vulkan::init => The window vulkan module has been initialized");
        }
        vulkan = &vulkan_engine;   // 借用:火山由应用持有与销毁,窗口火山不负责其生命周期
        surface.create(*id, vulkan->instance);
        find_graphics_queue_family(vulkan->physical_device);

        vulkan->create_logical_device(graphics_queue_family);
        command_pool.create(vulkan->device, graphics_queue_family);

        // 地面这些设置从火山初始化配置抄过来(应用是先批量加载 json、再 init 火山)
        ground.enabled = vulkan->init_info.ground;
        ground.grid_size = vulkan->init_info.ground_grid_size;
        ground.major_every = vulkan->init_info.ground_major_every;
        ground.fade_distance = vulkan->init_info.ground_fade_distance;
        ground.minor_color[0] = vulkan->init_info.ground_minor_red;
        ground.minor_color[1] = vulkan->init_info.ground_minor_green;
        ground.minor_color[2] = vulkan->init_info.ground_minor_blue;
        ground.minor_color[3] = vulkan->init_info.ground_minor_alpha;
        ground.major_color[0] = vulkan->init_info.ground_major_red;
        ground.major_color[1] = vulkan->init_info.ground_major_green;
        ground.major_color[2] = vulkan->init_info.ground_major_blue;
        ground.major_color[3] = vulkan->init_info.ground_major_alpha;
        ground.vertex_shader_file = vulkan->init_info.ground_vert;
        ground.fragment_shader_file = vulkan->init_info.ground_frag;

        initialized = true;

        // 窗口最小化时尺寸为 0,表面尚不可用:交换链留到尺寸恢复后由 rebuild 建立
        if (*pending_width == 0 || *pending_height == 0) {
            rebuild_flag = true;
            return;
        }
        create_swapchain(vulkan_engine);
        rebuild_flag = false;
    }
}
