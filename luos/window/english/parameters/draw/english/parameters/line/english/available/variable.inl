float x1{0.0f}, y1{0.0f}, z1{0.0f};   // 折线起点(三轴,世界坐标)
std::vector<Vector3> to_point{};      // 终点表(世界坐标):一个终点一段,相邻两点连成一段,空表不出顶点
float size_x{1.0f}, size_y{1.0f};     // 截面的两个几何值(局部 x/y,世界单位):线段方向是局部 z
float rotation_point_x{0.0f}, rotation_point_y{0.0f}, rotation_point_z{0.0f};   // 旋转中心(世界坐标,默认原点)
float rotation_x{0.0f}, rotation_y{0.0f}, rotation_z{0.0f};                     // 旋转角(度,依次绕 x、y、z)
uint8_t r{255}, g{255}, b{255};       // 线色(0~255)
float a{1.0f};                        // 线透明度(0~1)
bool use_texture{false};               // true 走贴图,false 走上面的 rgba
bool use_seal{false};                  // true 封边:把折线首尾接上,成一条闭合图形
std::string texture_key{};             // 贴图槽位键:文件路径,或"image:<像素地址>:<宽>x<高>"(直接给已加载好的图片);空 = 库内那张纯色
Information_image texture_image{};     // 直接给的已加载像素(浅拷贝:地址 + 宽高;渲染侧建槽位时读一次)
bool dirty{true};                     // 参数改过就要重算顶点
std::vector<Vertex> cache{};          // 本命令的顶点
