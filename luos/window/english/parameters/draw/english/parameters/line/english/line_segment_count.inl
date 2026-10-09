namespace Gnik_luos {
    size_t line_segment_count(const std::vector<Vector3>& point, double size_x, double size_y) {   // 有效段数:截面两个方向都没尺寸,或某段两端重合,这一段都不出顶点
        if (size_x <= 0.0 && size_y <= 0.0) {
            return 0;
        }
        size_t count = 0;
        for (size_t index = 1; index < point.size(); index++) {
            const Vector3& start = point[index - 1];
            const Vector3& end = point[index];
            const double x = end.x - start.x;
            const double y = end.y - start.y;
            const double z = end.z - start.z;
            if (x * x + y * y + z * z > 0.0) {
                count++;
            }
        }
        return count;
    }
}
