std::string name{"a window"};
int width{0};
int height{0};
std::string icon;
uint8_t display_index{0};
int logic_width{1600};
int logic_height{900};
bool is_time{true};
bool is_key{true};
bool is_vulkan{false};
// 嵌在 window_info 里的两个子段:线条渲染的着色器名、清屏色
std::string line_render_vert{"line.vert.spv"};
std::string line_render_frag{"line.frag.spv"};
float vulkan_clear_red{0.1f};
float vulkan_clear_green{0.1f};
float vulkan_clear_blue{0.1f};
float vulkan_clear_alpha{1.0f};
