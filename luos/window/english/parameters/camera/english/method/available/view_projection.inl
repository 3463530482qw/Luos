namespace Gnik_luos {
    // 世界 → 裁剪空间 = 视图 → 裁剪 × 世界 → 视图;投影里已经含了相机朝向与位置
    Matrix4 Camera::view_projection() const {
        return multiply(projection_view_space(), view_matrix());
    }
}
