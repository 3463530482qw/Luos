float x1{0.0f}, y1{0.0f}, z1{0.0f};   // 线段起点(三轴,世界坐标)
float x2{10.0f}, y2{10.0f}, z2{0.0f}; // 线段终点(三轴,世界坐标)
float thickness{1.0f};                // 线宽(世界单位)
uint8_t r{255}, g{255}, b{255};       // 线色(0~255)
float a{1.0f};                        // 线透明度(0~1)
Line_route route{};                   // 装配出来的路由
bool dirty{true};                     // 参数改过就要重算顶点
std::vector<Vertex> cache{};          // 本命令的顶点
