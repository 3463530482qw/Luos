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
Window_vulkan window_vulkan;   // 渲染子模块:先于下面两个引用构造,因为相机的实体与绘制器的实体都在别处,只借它转手
Camera& camera;   // 相机子模块:实体在 window_vulkan 里(与渲染模块同处构造一次绑死),这里只留引用
Draw drawer;      // 绘制器:实体归窗口,线条渲染器与窗口火山都只持引用(构造期绑定,之后一路有效)
bool is_time;
bool is_key;
bool is_vulkan;