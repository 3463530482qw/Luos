namespace Gnik_luos {
    // 关节面 = 角平分面:法线 = normalize(前段轴 + 后段轴);本段这一端的四个角沿本段轴延长 t = -(o·n)/(u·n)
    // 返回 false = 外扩超过 2 倍线宽(或两段正反向),这一处不当关节:四个 t 清零,调用方留着端面
    bool Line::private_miter(const Vector3& previous_axis, const Vector3& next_axis, double* shift) {
        const Vector3 sum{previous_axis.x + next_axis.x, previous_axis.y + next_axis.y, previous_axis.z + next_axis.z};
        const double sum_length = std::sqrt(dot(sum, sum));
        if (sum_length <= 0.0) {
            return false;
        }
        const Vector3 normal{sum.x / sum_length, sum.y / sum_length, sum.z / sum_length};
        const double along = dot(previous_axis, normal);
        const double half_x = size_x * 0.5;
        const double half_y = size_y * 0.5;
        const double side_scale[4]{-half_x, half_x, half_x, -half_x};
        const double up_scale[4]{-half_y, -half_y, half_y, half_y};
        double limit = 0.0;
        for (int quadrant = 0; quadrant < 4; quadrant++) {
            const Vector3 offset{
                private_side.x * side_scale[quadrant] + private_up.x * up_scale[quadrant],
                private_side.y * side_scale[quadrant] + private_up.y * up_scale[quadrant],
                private_side.z * side_scale[quadrant] + private_up.z * up_scale[quadrant]
            };
            const double value = along != 0.0 ? -dot(offset, normal) / along : 0.0;
            shift[quadrant] = value;
            limit = std::max(limit, std::fabs(value));
        }
        if (limit > size_x * 2.0) {
            for (int quadrant = 0; quadrant < 4; quadrant++) {
                shift[quadrant] = 0.0;
            }
            return false;
        }
        return true;
    }
}
