namespace Gnik_luos {
    Vector3 cross(const Vector3& left, const Vector3& right) {
        return Vector3{
            left.y * right.z - left.z * right.y,
            left.z * right.x - left.x * right.z,
            left.x * right.y - left.y * right.x
        };
    }
}
