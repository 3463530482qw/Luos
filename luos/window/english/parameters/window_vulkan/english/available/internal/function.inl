void find_graphics_queue_family();
vk::Rect2D viewport_rect();
void create_swapchain(uint32_t window_width, uint32_t window_height, float window_aspectratio, uint32_t logic_width);
void destroy_resources();
void rebuild();
void record_command_buffers();
void submit_frame();
