World_point position{};   // 相机位置(世界坐标,双精度);默认 (0,0,0) 时画布矩形左下角贴世界原点
double rotation_x{0.0}, rotation_y{0.0}, rotation_z{0.0};   // 按度,三个旋转依次施加
bool is_perspective{false};                 // 关 = 正交档(取景范围按画布,内容沿视线进深度)
double fov{60.0};                           // 垂直视场角(度),透视档用
double near_plane{1.0}, far_plane{10000.0}; // 透视档的近/远平面
double zoom{1.0};                           // 画布取景的缩放:1 = 画布尺寸就是世界单位尺寸
double canvas_width{1600.0}, canvas_height{900.0};   // 画布尺寸(世界单位,矩形也按它建)
