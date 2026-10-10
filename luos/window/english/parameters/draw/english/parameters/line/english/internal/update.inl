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
        // 展开图的列 = 每一段一列(零长段不占列):列数跟段数一致,同长的段列宽自然相等
        private_column.clear();
        private_total_length = 0.0;
        for (size_t index = 1; index < private_point.size(); index++) {
            const Vector3& start = private_point[index - 1];
            const Vector3& end = private_point[index];
            const double x = end.x - start.x;
            const double y = end.y - start.y;
            const double z = end.z - start.z;
            const double length = std::sqrt(x * x + y * y + z * z);
            if (length <= 0.0) {
                continue;   // 零长段不出顶点,也不占列
            }
            private_column.push_back(length);
            private_total_length += length;   // 展开图的宽 = 各列宽之和
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
