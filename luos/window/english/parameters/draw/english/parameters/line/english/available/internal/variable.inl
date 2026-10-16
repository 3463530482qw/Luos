double private_length{0.0};                                     // 本段长度
Vector3 private_axis{};                                         // 截面坐标系的局部 z:线段单位方向
Vector3 private_side{};                                         // 截面坐标系的局部 x:size_x 量的方向
Vector3 private_up{};                                           // 截面坐标系的局部 y:size_y 量的方向
Vector3 private_basis_x{}, private_basis_y{}, private_basis_z{}; // 旋转矩阵的三列
Vector3 private_start{}, private_end{};                         // 旋转之后的两端
std::vector<Vector3> private_point{};                           // 折线的点序列:起点在前,终点表顺次接上
std::vector<double> private_segment{};                          // 逐段长度(零长段不算):每段每面一块贴图,块的尺寸靠它算
std::vector<size_t> private_valid{};                            // 有效段(零长段不算)的点对下标
std::vector<Vector3> private_axis_list{};                       // 逐段轴:算关节延长量要用
std::vector<uint8_t> private_face_mask{};                       // 逐段留下哪几个面:bit0 起端面 / bit1 终端面 / bit2..5 = +x/-x/+y/-y
std::vector<double> private_head_shift{};                       // 逐段四个角在起端的延长量(关节面上的位置)
std::vector<double> private_tail_shift{};                       // 逐段四个角在终端的延长量
std::vector<size_t> private_vertex_begin{};                     // 逐段在本段顶点表里的起点
bool private_closed{false};                                     // 末点等于起点:首尾接上的闭合折线
uint8_t private_step_count{0};                                  // 路由里装了几步:没段可铺就装 0 步
