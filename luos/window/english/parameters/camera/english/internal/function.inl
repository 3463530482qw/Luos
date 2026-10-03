double private_aspect() const;   // 视口宽 / 视口高,取景范围自己算,调用方不再各算一份
Rotation_basis private_rotation_basis() const;
Vector3 private_view_origin() const;   // 相机在视图空间的站位 = 画布矩形中心
Vector3 private_view_direction(const Vector3& view_direction) const;   // 视图空间方向 → 世界方向
Matrix4 private_perspective_matrix(double aspect) const;
Matrix4 private_orthographic_matrix() const;
double private_fit_distance() const;   // 画布精确塞进取景框需要的距离
