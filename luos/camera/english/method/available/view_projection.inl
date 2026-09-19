namespace Gnik_luos {
    // 世界 → 裁剪空间(aspect = 视口宽 / 视口高,只有透视档用得上)
    Matrix4 Camera::view_projection(float aspect) const {
        if (!is_perspective) {
            return private_orthographic_matrix();   // 2D 档:位置定画面中心,旋转不参与
        }
        return private_multiply(private_perspective_matrix(aspect), private_view_matrix());
    }
}
