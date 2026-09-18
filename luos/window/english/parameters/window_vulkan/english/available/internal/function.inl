void find_graphics_queue_family(vk::raii::PhysicalDevice& physical_device);
void create_swapchain(Vulkan& vulkan_engine);
void rebuild();
void destroy_resources();
vk::Rect2D viewport_rect();
void record_command_buffers();
void submit_frame();
