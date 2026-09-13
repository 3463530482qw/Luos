namespace Gnik_luos {
    // 封边:上/中/下 在端头接一个等腰三角形,底是端头那条边,尖落在延伸点上(可能偏到上沿或下沿)
    // 上下一块 是三角形负形:端头挖掉一个三角形,剩下上下两块尖与线身连成一体
    void Draw_line_cmd::private_edge_cap() {
        if (!private_edge_on || private_length <= 0.0f) {
            return;
        }
        for (int side = 0; side < 2; side++) {
            bool at_begin = (side == 0);
            if (at_begin ? !private_cap_begin : !private_cap_end) {
                continue;
            }
            float sign = at_begin ? -1.0f : 1.0f;   // 朝外的方向
            float base_x = at_begin ? private_ax : private_bx;   // 回缩后的端头(也是底边中点)
            float base_y = at_begin ? private_ay : private_by;
            float end_x = at_begin ? private_sx : private_ex;    // 回缩前的端头
            float end_y = at_begin ? private_sy : private_ey;
            if (private_cap_notch) {
                // 负形:两块尖分别压在端面的上沿与下沿,往回收缩到中线上的同一点
                const std::array<std::array<float, 2>, 4> upper{{
                    {base_x - private_nx, base_y - private_ny},
                    {end_x - private_nx, end_y - private_ny},
                    {base_x, base_y},
                    {base_x, base_y}
                }};
                const std::array<std::array<float, 2>, 4> lower{{
                    {base_x + private_nx, base_y + private_ny},
                    {end_x + private_nx, end_y + private_ny},
                    {base_x, base_y},
                    {base_x, base_y}
                }};
                private_edge_triangle(upper);
                private_edge_triangle(lower);
                continue;
            }
            const std::array<std::array<float, 2>, 4> cap{{
                {base_x + private_nx, base_y + private_ny},
                {base_x - private_nx, base_y - private_ny},
                {
                    base_x + private_dx * private_cap_forward * sign + private_cap_lateral * private_nx,
                    base_y + private_dy * private_cap_forward * sign + private_cap_lateral * private_ny
                },
                {
                    base_x + private_dx * private_cap_forward * sign + private_cap_lateral * private_nx,
                    base_y + private_dy * private_cap_forward * sign + private_cap_lateral * private_ny
                }
            }};
            private_edge_triangle(cap);
        }
    }
}
