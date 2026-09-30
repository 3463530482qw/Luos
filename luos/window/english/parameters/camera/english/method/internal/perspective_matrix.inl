namespace Gnik_luos {
    // 透视:把视锥压进 NDC(输入的 z 是视图空间,越负越远)
    //   Vulkan 裁剪空间 z ∈ [0, 1]:z_view = -near → 0,z_view = -far → 1;w = -z_view(距离)
    //   y 不额外翻转:视图空间的 y 与世界的 y 同向都朝下,NDC 的 y 也朝下,三者一致
    //   x 按 aspect 缩放:aspect = 视口宽 / 视口高,fov 是纵向视场角
    Matrix4 Camera::private_perspective_matrix(double aspect) const {
        const double f = 1.0 / std::tan(fov * 0.5 * pi / 180.0);
        const double near_value = (near_plane > 0.0) ? near_plane : near_min;
        const double far_value = (far_plane > near_value) ? far_plane : near_value + 1.0;

        Matrix4 matrix;
        for (double& value : matrix.m) {
            value = 0.0;
        }
        matrix.m[0] = f / ((aspect > 0.0) ? aspect : 1.0);
        matrix.m[5] = f;
        matrix.m[10] = far_value / (near_value - far_value);
        matrix.m[11] = -1.0;
        matrix.m[14] = far_value * near_value / (near_value - far_value);
        return matrix;
    }
}
