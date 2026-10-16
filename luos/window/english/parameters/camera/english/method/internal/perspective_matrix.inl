namespace Gnik_luos {
    // 透视:把视锥压进 NDC(输入的 z 是视图空间,前方距离 d 为正)
    //   Vulkan 裁剪空间 z ∈ [0, 1]:d = near → 0,d = far → 1;w = d(前方距离,正数)
    //   z_row = +F/(F-N)、z_const = -FN/(F-N):代入 d = N 得 0,代入 d = F 得 w(即分母) → ndc_z = 1
    //   纵向取负号:视图 y 向上,而裁剪空间的 y 朝下(Vulkan 口径),翻过来画布才对得上(x 右、y 上)
    Matrix4 Camera::private_perspective_matrix(double aspect) const {
        const double f = 1.0 / std::tan(fov * 0.5 * pi / 180.0);
        const double near_value = (near_plane > 0.0) ? near_plane : near_min;
        const double far_value = (far_plane > near_value) ? far_plane : near_value + 1.0;
        const double depth = far_value - near_value;

        Matrix4 matrix;
        for (double& value : matrix.m) {
            value = 0.0;
        }
        matrix.m[0] = f / ((aspect > 0.0) ? aspect : 1.0);
        matrix.m[5] = -f;
        matrix.m[10] = far_value / depth;
        matrix.m[11] = 1.0;
        matrix.m[14] = -far_value * near_value / depth;
        return matrix;
    }
}
