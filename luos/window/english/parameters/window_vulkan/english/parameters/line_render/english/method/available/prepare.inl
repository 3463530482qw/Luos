namespace Gnik_luos {
    void Vulkan_line_render::prepare() {
        vertex_count = 0;
        if (pipeline == nullptr || vertex.empty()) {
            vertex.clear();
            return;
        }

        size_t bytes = vertex.size() * sizeof(Vertex);
        if (bytes > vertex_capacity) {
            // 顶点变多就扩容:prepare 在帧围栏之后调用,上一帧的 GPU 工作已结束,重建缓冲安全
            // 一次翻倍留出余量,免得顶点数在容量附近来回时每帧重建
            vulkan().device.waitIdle();
            create_vertex_buffer(std::max(bytes, vertex_capacity * 2));
        }

        // 双缓冲交替:GPU 读上一帧那块,这里写另一块
        vertex_frame = (vertex_frame + 1) % 2;
        void* mapped = vertex_memory[vertex_frame].mapMemory(0, bytes);
        std::memcpy(mapped, vertex.data(), bytes);
        vertex_memory[vertex_frame].unmapMemory();

        // 投影只由相机给:世界 → 裁剪在相机里算完(double),这里收窄成推常量要的 float
        push_constants = {};
        std::array<float, 16> packed = to_float16(camera.view_projection());
        std::memcpy(push_constants.mvp, packed.data(), packed.size() * sizeof(float));
        push_constants.screen_w = static_cast<float>(frame_extent.width);
        push_constants.screen_h = static_cast<float>(frame_extent.height);
        push_constants.snap_pixel = snap_pixel ? 1.0f : 0.0f;

        vertex_count = static_cast<uint32_t>(vertex.size());
        vertex.clear();   // 本帧顶点已交给 GPU,列表清空等下一帧追加
    }
}
