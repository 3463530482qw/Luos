double private_length{0.0};                                     // 本段长度
Vector3 private_axis{};                                         // 截面坐标系的局部 z:线段单位方向
Vector3 private_side{};                                         // 截面坐标系的局部 x:size_x 量的方向
Vector3 private_up{};                                           // 截面坐标系的局部 y:size_y 量的方向
Vector3 private_basis_x{}, private_basis_y{}, private_basis_z{}; // 旋转矩阵的三列
Vector3 private_start{}, private_end{};                         // 旋转之后的两端
std::vector<Vector3> private_point{};                           // 折线的点序列:起点在前,终点表顺次接上
std::vector<double> private_segment{};                          // 逐段长度(零长段不算):每段每面一块贴图,块的尺寸靠它算
uint8_t private_step_count{0};                                  // 路由里装了几步:没段可铺就装 0 步
double temporary_x{}, temporary_y{}, temporary_z{};             // 读一组坐标值的中转
int64_t temporary_color{};                                      // 读一个颜色分量的中转
bool temporary_flag{false};                                     // 读一个开关的中转
std::string_view temporary_text{};                              // 读一个字符串的中转
