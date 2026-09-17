Vulkan_viewport viewport;
uint32_t *pending_width, *pending_height;
SDL_Window** id;
bool initialized{false};
Vulkan_surface surface;
Vulkan_command_pool command_pool;
bool rebuild_flag{false};