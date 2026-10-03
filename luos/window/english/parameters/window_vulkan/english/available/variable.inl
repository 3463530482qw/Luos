Vulkan_viewport viewport;
Camera camera;    // 相机子模块:就放在使用它的渲染模块前头,构造顺序即绑定顺序
Draw& drawer;      // 绘制器:实体归窗口,构造期绑死,之后不再判空
Window* host{nullptr};   // 宿主窗口:视口量按"用的时候现取"从这里读,不落下成员指针
SDL_Window** id;         // 窗口句柄的位置(表面创建要用)
bool initialized{false};
Vulkan_surface surface;
Vulkan_command_pool command_pool;
bool rebuild_flag{false};
Vulkan_swapchain swapchain;
Vulkan_renderpass renderpass;
Vulkan_depth depth;
Vulkan_framebuffer framebuffer;
Vulkan_command_buffer command_buffer;
Vulkan_synchronization synchronization;
Vulkan_line_render line_render;
Vulkan_ground ground;
