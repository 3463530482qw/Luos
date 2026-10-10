double private_length{0.0};                                     // 本段长度
Vector3 private_axis{};                                         // 截面坐标系的局部 z:线段单位方向
Vector3 private_side{};                                         // 截面坐标系的局部 x:size_x 量的方向
Vector3 private_up{};                                           // 截面坐标系的局部 y:size_y 量的方向
Vector3 private_basis_x{}, private_basis_y{}, private_basis_z{}; // 旋转矩阵的三列
Vector3 private_start{}, private_end{};                         // 旋转之后的两端
std::vector<Vector3> private_point{};                           // 折线的点序列:起点在前,终点表顺次接上
std::vector<double> private_column{};                            // 展开图的列 = 去重后的段长:同长的段共用一列
double private_total_length{0.0};                               // 展开图的宽 = 各列宽之和(同一路径取最长那条命令)
double private_u0{0.0}, private_u1{0.0};                        // 本段两端的 u(世界单位,落在本段那一列里)
uint8_t private_step_count{0};                                  // 路由里装了几步:没段可铺就装 0 步
double temporary_x{}, temporary_y{}, temporary_z{};             // 读一组坐标值的中转
int64_t temporary_color{};                                      // 读一个颜色分量的中转
bool temporary_flag{false};                                     // 读一个开关的中转
std::string_view temporary_text{};                              // 读一个字符串的中转