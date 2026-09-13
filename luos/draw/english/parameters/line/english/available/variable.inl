float x1{0.0f}, y1{0.0f};            // 线段起点
float x2{10.0f}, y2{10.0f};          // 线段终点
float thickness{1.0f};       //线宽
float rotate{0.0f};          // 旋转弧度
float rox{10.0f}, roy{10.0f};        // 旋转中心
std::array<uint8_t, 2> r{255, 255};  // 颜色与透明度都按 [起点, 终点] 两端给
std::array<uint8_t, 2> g{255, 255};
std::array<uint8_t, 2> b{255, 255};
std::array<float, 2> a{1.0f, 1.0f};
float dash_length{6.0f};
float dash_gap{4.0f};
Line_cmd_label label{};
bool ended{false};   //路径首尾封口:末点没回到起点就补一段接回去
bool cmd_update{true}; //用于缓存更新，调用函数后设为true计算完成后设为flase
