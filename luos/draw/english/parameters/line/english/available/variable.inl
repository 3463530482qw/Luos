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
std::array<uint8_t, 3> inside_color{0, 0, 0};    // 内部填充 rgb(开关关掉就不用)
float inside_alpha{0.0f};                        // 内部填充透明度,和线条颜色一样用 0~1
std::array<uint8_t, 3> outside_color{0, 0, 0};   // 外部填充 rgb
float outside_alpha{0.0f};                       // 外部填充透明度
Line_cmd_label label{};
Camera* camera{nullptr};   // 外部填充要知道相机画面,由 Draw::bind_camera 接上
bool ended{false};   //路径首尾封口:末点没回到起点就补一段接回去
bool cmd_update{true}; //用于缓存更新，调用函数后设为true计算完成后设为flase
