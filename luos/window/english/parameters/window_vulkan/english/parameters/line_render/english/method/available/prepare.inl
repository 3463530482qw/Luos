namespace Gnik_luos {
    void Vulkan_line_render::prepare(float logic_width, float logic_height) {
        vertex_count = 0;
        if (pipeline == nullptr || vertex.empty() || logic_width <= 0.0f || logic_height <= 0.0f) {
            vertex.clear();
            return;
        }

        size_t bytes = vertex.size() * sizeof(Vertex);
        if (bytes > vertex_capacity) {
            // 顶点变多就扩容:prepare 在帧围栏之后调用,上一帧的 GPU 工作已结束,重建缓冲安全
            // 一次翻倍留出余量,免得顶点数在容量附近来回时每帧重建
            (*vulkan)->device.waitIdle();
            create_vertex_buffer(std::max(bytes, vertex_capacity * 2));
        }

        // 双缓冲交替:GPU 读上一帧那块,这里写另一块
        vertex_frame = (vertex_frame + 1) % 2;
        void* mapped = vertex_memory[vertex_frame].mapMemory(0, bytes);
        std::memcpy(mapped, vertex.data(), bytes);
        vertex_memory[vertex_frame].unmapMemory();

        // 投影:接了相机就按相机算(正交档 = 画布 → NDC,z 直通深度;透视档 = 视图 × 透视);
        // 没接相机时沿用画布 → NDC 的线性映射(y 向下),与加相机之前逐项一致
        push_constants = {};
        if (camera != nullptr) {
            Matrix4 matrix = camera->view_projection(logic_width / logic_height);
            std::memcpy(push_constants.mvp, matrix.m, sizeof(float) * 16);
        } else {
            push_constants.mvp[0] = 2.0f / logic_width;
            push_constants.mvp[5] = 2.0f / logic_height;
            push_constants.mvp[10] = 1.0f;
            push_constants.mvp[12] = -1.0f;
            push_constants.mvp[13] = -1.0f;
            push_constants.mvp[15] = 1.0f;
        }
        push_constants.screen_w = static_cast<float>(frame_extent.width);
        push_constants.screen_h = static_cast<float>(frame_extent.height);
        push_constants.snap_pixel = snap_pixel ? 1.0f : 0.0f;

        vertex_count = static_cast<uint32_t>(vertex.size());
        vertex.clear();   // 本帧顶点已交给 GPU,列表清空等下一帧追加
    }
}
