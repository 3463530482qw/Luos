double private_length{0.0};                                     // 本段长度
Vector3 private_axis{};                                         // 截面坐标系的局部 z:线段单位方向
Vector3 private_side{};                                         // 截面坐标系的局部 x:size_x 量的方向
Vector3 private_up{};                                           // 截面坐标系的局部 y:size_y 量的方向
Vector3 private_basis_x{}, private_basis_y{}, private_basis_z{}; // 旋转矩阵的三列
Vector3 private_start{}, private_end{};                         // 旋转之后的两端
uint8_t private_step_count{0};                                  // 路由里装了几步:退化线装 0 步
