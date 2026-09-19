Rotation_basis private_rotation_basis() const;
Matrix4 private_view_matrix() const;
Matrix4 private_perspective_matrix(float aspect) const;
Matrix4 private_orthographic_matrix() const;
Matrix4 private_multiply(const Matrix4& left, const Matrix4& right) const;
