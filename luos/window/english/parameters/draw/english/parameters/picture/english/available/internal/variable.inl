Vector3 private_basis_x{}, private_basis_y{}, private_basis_z{};   // 旋转矩阵的三列
Vector3 private_corner[4]{};                                       // 四个角:0 (x1,y1) → 1 (x2,y1) → 2 (x2,y2) → 3 (x1,y2)
bool private_ready{false};                                         // 位置与宽高都齐了才出顶点:库里不替它编一个形状
