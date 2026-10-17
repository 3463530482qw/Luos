Vector3 private_basis_x{}, private_basis_y{}, private_basis_z{};   // 旋转矩阵的三列
std::vector<std::function<void()>> private_route{};   // 路由表:按序跑,每条命令自己装步骤
