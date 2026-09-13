//用于存放顶点缓存之类的
std::vector<Vertex> private_vertex{};                    // 本命令这条路径的几何
std::vector<Line_point> private_point{};                 // 链条顶点,每点带那一段的颜色快照
std::vector<void (Draw_line_cmd::*)()> private_step{};   // 效果管线
Line_cmd_label private_label{};                          // 上次路由的标志快照
bool private_rotate_on{false};
bool private_routed{false};
float private_sx{0.0f}, private_sy{0.0f};                // 本段原始两端
float private_ex{0.0f}, private_ey{0.0f};
float private_ax{0.0f}, private_ay{0.0f};                // 本段进管线的两端
float private_bx{0.0f}, private_by{0.0f};
float private_nx{0.0f}, private_ny{0.0f};                // 线宽半宽法线
float private_length{0.0f};
size_t private_emit_begin{0};                            // 本段顶点在缓存中的起点
float private_u0{0.0f}, private_u1{1.0f};                // 本段两端在整条路径上的进度
float private_path_length{0.0f};
float private_dash_begin{0.0f};                          // 本段起点在整条路径上的弧长
std::array<uint8_t, 2> private_er{255, 255};             // 本段实际用的颜色
std::array<uint8_t, 2> private_eg{255, 255};
std::array<uint8_t, 2> private_eb{255, 255};
std::array<float, 2> private_ea{1.0f, 1.0f};
bool private_trailing{false};                            // 链尾改过色
