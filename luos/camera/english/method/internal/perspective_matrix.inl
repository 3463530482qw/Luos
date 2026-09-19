namespace Gnik_luos {
    // 透视:把视锥压进 NDC。Vulkan 的裁剪空间 z 是 [0, 1](近平面 0、远平面 1),w 取 -z_view;
    // y 不额外翻转 —— 世界的 y 朝下(画布口径),NDC 的 y 也朝下,两者一致
    Matrix4 Camera::private_perspective_matrix(float aspect) const {
        constexpr float pi = 3.14159265358979323846f;
        const float f = 1.0f / std::tan(fov * 0.5f * pi / 180.0f);
        const float near_value = (near_plane > 0.0f) ? near_plane : 0.0001f;
        const float far_value = (far_plane > near_value) ? far_plane : near_value + 1.0f;

        Matrix4 matrix;
        for (float& value : matrix.m) {
            value = 0.0f;
        }
        matrix.m[0] = f / ((aspect > 0.0f) ? aspect : 1.0f);
        matrix.m[5] = f;
        matrix.m[10] = far_value / (near_value - far_value);
        matrix.m[11] = -1.0f;
        matrix.m[14] = far_value * near_value / (near_value - far_value);
        return matrix;
    }
}
