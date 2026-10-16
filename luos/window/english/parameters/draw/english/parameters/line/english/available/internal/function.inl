void private_rebuild_route();
void private_run_route();
void private_build_frame(size_t index);
void private_rotate();
Vector3 private_rotate_vector(const Vector3& value, const Vector3& pivot) const;
void private_box(size_t offset, size_t ordinal);
bool private_miter(const Vector3& previous_axis, const Vector3& next_axis, double* shift);
void private_rgba();
