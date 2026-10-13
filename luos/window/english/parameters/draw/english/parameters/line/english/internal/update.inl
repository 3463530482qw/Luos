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
        if (use_seal) {
            const Vector3 head = private_point.front();   // 按值拷一份:免得 push_back 扩容把引用弄失效
            private_point.push_back(head);                // 封边:首尾接上;本来就闭合时这一对零长,后面会被丢掉
        }
        private_segment.clear();
        cache.clear();
        private_valid.clear();
        private_axis_list.clear();
        if (size_x > 0.0 || size_y > 0.0) {
            for (size_t index = 0; index + 1 < private_point.size(); index++) {
                private_build_frame(index);
                if (private_length <= 0.0) {
                    continue;   // 零长段不占段号:关节看的是有效段
                }
                private_valid.push_back(index);
                private_axis_list.push_back(private_axis);
            }
        }
        const Vector3& head = private_point.front();
        const Vector3& tail = private_point.back();
        private_closed = private_point.size() > 2 && head.x == tail.x && head.y == tail.y && head.z == tail.z;

        const size_t count = private_valid.size();
        private_face_mask.assign(count, 0x3F);
        private_head_shift.assign(count * 4, 0.0);
        private_tail_shift.assign(count * 4, 0.0);
        private_vertex_begin.assign(count, 0);
        for (size_t ordinal = 0; ordinal < count; ordinal++) {
            private_build_frame(private_valid[ordinal]);
            if (ordinal > 0 || private_closed) {
                const Vector3& previous = ordinal > 0 ? private_axis_list[ordinal - 1] : private_axis_list[count - 1];
                if (private_miter(previous, private_axis, &private_head_shift[ordinal * 4])) {
                    private_face_mask[ordinal] &= static_cast<uint8_t>(~0x01);   // 连接处:起端面不生成
                }
            }
            if (ordinal + 1 < count || private_closed) {
                const Vector3& next = ordinal + 1 < count ? private_axis_list[ordinal + 1] : private_axis_list[0];
                if (private_miter(private_axis, next, &private_tail_shift[ordinal * 4])) {
                    private_face_mask[ordinal] &= static_cast<uint8_t>(~0x02);   // 连接处:终端面不生成
                }
            }
        }

        size_t total = 0;
        for (size_t ordinal = 0; ordinal < count; ordinal++) {
            private_vertex_begin[ordinal] = total;
            for (int bit = 0; bit < 6; bit++) {
                total += (private_face_mask[ordinal] & (1 << bit)) != 0 ? 6 : 0;
            }
        }
        if (total > 0) {
            cache.resize(total);   // 留下的面各摊两个三角形
        }
        private_rebuild_route();
        private_run_route();
        dirty = false;
    }
}
