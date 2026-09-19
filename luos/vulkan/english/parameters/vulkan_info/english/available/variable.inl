std::string window_name{"a window"};
std::vector<const char*> extension;
Vulkan_debug_info debug_info;

// 无限地面:默认开(像引擎编辑器那样有个参照地面),参数从 json 的 vulkan_info.ground 子段来
bool ground{true};
float ground_grid_size{100.0f};         // 小格边长(世界单位)
float ground_major_every{10.0f};        // 每几格一条主线
float ground_fade_distance{8000.0f};    // 离相机地面投影多远淡出到看不见
float ground_minor_red{0.42f}, ground_minor_green{0.44f}, ground_minor_blue{0.5f}, ground_minor_alpha{0.5f};
float ground_major_red{0.72f}, ground_major_green{0.74f}, ground_major_blue{0.8f}, ground_major_alpha{0.85f};
std::string ground_vert{"ground.vert.spv"};
std::string ground_frag{"ground.frag.spv"};
