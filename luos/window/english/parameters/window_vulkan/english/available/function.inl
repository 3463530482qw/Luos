void initialize(Vulkan& vulkan, SDL_Window* window, uint32_t window_width, uint32_t window_height, float window_aspectratio, uint32_t logic_width);
void draw_frame();
void destroy();
void request_rebuild(uint32_t window_width, uint32_t window_height, float window_aspectratio = 0.0f);
bool is_initialized();
