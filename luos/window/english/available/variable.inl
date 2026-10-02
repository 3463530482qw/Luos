uint8_t display_index{0};  
uint32_t width{0}, height{0};
uint32_t logic_width{1600};
uint32_t logic_height{900};
float aspectratio{0};
float logic_aspectratio{0};
std::string icon;
std::string name{"a window"};
SDL_Window* id{nullptr};
bool isrun{true};
World world;      // 世界坐标子模块:世界空间的约定与射线求交
Window_time time;
window_mouse mouse;
Key_board key;
Camera& camera;   // 相机子模块:实体放在 window_vulkan 里(与渲染模块同处构造一次绑死),这里只留引用
Draw& drawer;     // 绘制器:实体同样在 window_vulkan 里,窗口每帧把可见矩形交给它
Window_vulkan window_vulkan;
bool is_time;
bool is_key;
bool is_vulkan;