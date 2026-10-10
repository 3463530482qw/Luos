namespace Gnik_luos {
    void Line::update() {
        if (!dirty) {
            return;   // 参数没动:顶点还是上一次算的,不重算
        }
        private_point.clear();
        private_point.push_back(Vector3{x1, y1, z1});
        for (const Vector3& point : to_point) {
            private_point.push_back(point);
        }
        private_total_length = 0.0;
        for (size_t index = 1; index < private_point.size(); index++) {
            const Vector3& start = private_point[index - 1];
            const Vector3& end = private_point[index];
            const double x = end.x - start.x;
            const double y = end.y - start.y;
            const double z = end.z - start.z;
            private_total_length += std::sqrt(x * x + y * y + z * z);   // uv 的 u 按整条折线的长度归一
        }
        cache.clear();
        const size_t segment_count = line_segment_count(private_point, size_x, size_y);
        if (segment_count > 0) {
            cache.resize(segment_count * 36);   // 一段一个立体:六个面十二个三角形
        }
        private_rebuild_route();
        private_run_route();
        dirty = false;
    }
}
