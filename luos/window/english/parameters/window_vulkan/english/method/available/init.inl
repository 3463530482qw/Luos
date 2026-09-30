namespace Gnik_luos {
    // 借用火山:应用先 init 火山,再把同一个对象交给窗口火山;引用一路有效到窗口火山销毁
    // 视口量在 create_swapchain / rebuild 里现从宿主窗口读,不在构造期落下快照
    void Window_vulkan::init(Vulkan& vulkan_engine) {
        if (initialized) {
            throw std::runtime_error("Window_vulkan::init => The window vulkan module has been initialized");
        }
        vulkan_borrowed = &vulkan_engine;
        Vulkan& engine = *vulkan_borrowed;
        surface.create(*id, engine.instance);
        find_graphics_queue_family(engine.physical_device);

        engine.create_logical_device(graphics_queue_family);
        command_pool.create(engine.device, graphics_queue_family);

        // 地面这些设置从火山初始化配置抄过来(应用是先批量加载 json、再 init 火山)
        ground.enabled = engine.init_info.ground;
        ground.grid_size = engine.init_info.ground_grid_size;
        ground.major_every = engine.init_info.ground_major_every;
        ground.fade_distance = engine.init_info.ground_fade_distance;
        ground.minor_color[0] = engine.init_info.ground_minor_red;
        ground.minor_color[1] = engine.init_info.ground_minor_green;
        ground.minor_color[2] = engine.init_info.ground_minor_blue;
        ground.minor_color[3] = engine.init_info.ground_minor_alpha;
        ground.major_color[0] = engine.init_info.ground_major_red;
        ground.major_color[1] = engine.init_info.ground_major_green;
        ground.major_color[2] = engine.init_info.ground_major_blue;
        ground.major_color[3] = engine.init_info.ground_major_alpha;
        ground.vertex_shader_file = engine.init_info.ground_vert;
        ground.fragment_shader_file = engine.init_info.ground_frag;

        initialized = true;

        // 视口按当前窗口量重算一次:窗口尺寸为 0(最小化)时留到下一帧 rebuild
        update_viewport();
        if (viewport.width == 0 || viewport.height == 0) {
            rebuild_flag = true;
            return;
        }
        create_swapchain(engine);
        rebuild_flag = false;
    }
}
