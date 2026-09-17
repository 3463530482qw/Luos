void find_graphics_queue_family(vk::raii::PhysicalDevice& physical_device);
void create_swapchain(Vulkan& vulkan);
vk::Rect2D viewport_rect();
void record_command_buffers();