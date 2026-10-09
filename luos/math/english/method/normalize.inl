namespace Gnik_luos {
    // 单位化:零向量原样返回,退化与否由调用侧自己判
    Vector3 normalize(const Vector3& value) {
        const double length = std::sqrt(value.x * value.x + value.y * value.y + value.z * value.z);
        if (length <= 0.0) {
            return value;
        }
        return Vector3{value.x / length, value.y / length, value.z / length};
    }
}
