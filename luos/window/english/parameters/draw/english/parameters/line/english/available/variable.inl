float x1{0.0f}, y1{0.0f}, z1{0.0f};   // 线段起点(三轴,世界坐标)
float x2{10.0f}, y2{10.0f}, z2{0.0f}; // 线段终点(三轴,世界坐标)
float size_x{1.0f}, size_y{1.0f};     // 截面的两个几何值(局部 x/y,世界单位):线段方向是局部 z
float rotation_point_x{0.0f}, rotation_point_y{0.0f}, rotation_point_z{0.0f};   // 旋转中心(世界坐标,默认原点)
float rotation_x{0.0f}, rotation_y{0.0f}, rotation_z{0.0f};                     // 旋转角(度,依次绕 x、y、z)
uint8_t r{255}, g{255}, b{255};       // 线色(0~255)
float a{1.0f};                        // 线透明度(0~1)
bool dirty{true};                     // 参数改过就要重算顶点
std::vector<Vertex> cache{};          // 本命令的顶点
