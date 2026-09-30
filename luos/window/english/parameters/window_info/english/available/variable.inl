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
// 子段 camera:窗口的子模块相机的初始取景(缺省:正交档、位置就是默认值 (0,0,0))
// 位置为默认 (0,0,0) 时画布矩形左下角贴世界原点;非默认时画布跟着平移
bool has_camera{false};
bool camera_is_perspective{false};
double camera_x{0.0};
double camera_y{0.0};
double camera_z{0.0};
double camera_rotation_x{0.0};
double camera_rotation_y{0.0};
double camera_rotation_z{0.0};
double camera_fov{60.0};
double camera_near_plane{1.0};
double camera_far_plane{10000.0};
double camera_zoom{1.0};
