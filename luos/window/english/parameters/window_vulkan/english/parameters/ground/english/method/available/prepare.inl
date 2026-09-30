namespace Gnik_luos {
    void Vulkan_ground::prepare() {
        if (pipeline == nullptr || !enabled) {
            return;
        }

        // 地面四边形以相机在地面上的投影为中心(y 恒 0 = 地面那个平面),半径取淡出距离的 1.5 倍:
        // 淡出范围之外本来就看不见,所以"无限"靠的是四边形跟着相机走
        const double height = std::fabs(camera.position.position.y);
        const double radius = std::max(static_cast<double>(fade_distance) * 1.5, height * 4.0);

        Matrix4 matrix = camera.view_projection();
        push_constants = {};
        std::array<float, 16> packed = to_float16(matrix);
        std::memcpy(push_constants.mvp, packed.data(), packed.size() * sizeof(float));
        for (int index = 0; index < 4; index++) {
            push_constants.minor_color[index] = minor_color[index];
            push_constants.major_color[index] = major_color[index];
        }
        push_constants.grid_params[0] = (grid_size > 0.0f) ? grid_size : 1.0f;
        push_constants.grid_params[1] = (major_every > 1.0f) ? major_every : 1.0f;
        push_constants.grid_params[2] = (fade_distance > 0.0f) ? fade_distance : 1.0f;
        push_constants.grid_params[3] = static_cast<float>((radius > 0.0) ? radius : 1.0);
        push_constants.eye_ground[0] = static_cast<float>(camera.position.position.x);
        push_constants.eye_ground[1] = static_cast<float>(camera.position.position.z);
    }
}
