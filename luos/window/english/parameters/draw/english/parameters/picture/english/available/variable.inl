float x1{0.0f}, y1{0.0f}, z1{0.0f};    // 一个角(世界坐标):data 给的那个点
float x2{0.0f}, y2{0.0f}, z2{0.0f};    // 对角:data 给的第二个点
float rotation_x{0.0f}, rotation_y{0.0f}, rotation_z{0.0f};                     // 旋转角(度,依次绕 x、y、z)
float rotation_point_x{0.0f}, rotation_point_y{0.0f}, rotation_point_z{0.0f};   // 旋转中心(世界坐标,默认原点)
uint8_t r[4]{255, 255, 255, 255}, g[4]{255, 255, 255, 255}, b[4]{255, 255, 255, 255};   // 四个顶点各自的色(0~255)
float a[4]{1.0f, 1.0f, 1.0f, 1.0f};    // 四个顶点各自的透明度(0~1)
bool use_texture{false};               // true 走贴图(颜色乘上去),false 只走四角的 rgba
Sprite_sheet sprite_sheet{};           // 图集怎么切(只切一格;帧动画的选项后续再加)
int sheet_index{0};                    // 取第几格(行主序)
std::string texture_key{};             // 贴图键:单个图片文件,或"image:<像素地址>:<宽>x<高>"(直接给像素);空 = 库内那张纯色
Information_image texture_image{};     // 直接给的已加载像素(浅拷贝:地址 + 宽高;渲染侧建槽位时读一次)
bool dirty{true};                      // 参数改过就要重算顶点
std::vector<Vertex> cache{};           // 本命令的顶点(四个角摊成两个三角形)
