namespace Gnik_luos {
    double dot(const Vector3& left, const Vector3& right) {
        return left.x * right.x + left.y * right.y + left.z * right.z;
    }
}
