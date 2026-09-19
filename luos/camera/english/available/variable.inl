float x{0.0f}, y{0.0f}, z{0.0f};                            // 相机位置(世界坐标)
float rotation_x{0.0f}, rotation_y{0.0f}, rotation_z{0.0f}; // 绕 x/y/z 的旋转(度),依次施加,合起来决定看向哪
bool is_perspective{false};                                 // 关 = 正交档(2D:世界 xy 就是画布像素、z 直通深度)
float fov{60.0f};                                           // 垂直视场角(度),透视档用
float near_plane{1.0f}, far_plane{10000.0f};                // 透视档的近/远平面
float zoom{1.0f};                                           // 正交档的缩放
float canvas_width{1600.0f}, canvas_height{900.0f};         // 正交档对应的画布尺寸
