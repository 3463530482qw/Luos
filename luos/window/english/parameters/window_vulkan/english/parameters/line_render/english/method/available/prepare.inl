namespace Gnik_luos {
    void Vulkan_line_render::prepare() {
        vertex_count = 0;
        group_texture.clear();
        group_descriptor.clear();
        group_scale.clear();
        group_range.clear();
        if (pipeline == nullptr || vertex.empty()) {
            vertex.clear();
            span.clear();
            return;
        }

        // 本帧要画几组:相邻同贴图的段并成一组,组数就是后面的 draw 次数
        for (const Line_span& item : span) {
            if (!group_texture.empty() && group_texture.back() == item.texture_key) {
                group_range.back()[1] += static_cast<uint32_t>(item.count);
                continue;
            }
            group_texture.push_back(item.texture_key);
            group_range.push_back({static_cast<uint32_t>(item.begin), static_cast<uint32_t>(item.count)});
        }

        // 每组取描述符与展开尺度:同一个键的段得先收齐 —— 展开图按最长的那条命令定,短的只占图里一部分
        for (const std::string& key : group_texture) {
            std::vector<Line_span> usage;
            for (const Line_span& item : span) {
                if (item.texture_key == key) {
                    usage.push_back(item);
                }
            }
            group_descriptor.push_back(*texture().descriptor(key, usage));
            const Texture_slot& slot = texture().slot_of(key);
            group_scale.push_back({
                static_cast<float>(1.0 / slot.world_width),
                static_cast<float>(1.0 / slot.world_height)
            });
        }
        span.clear();

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

        // 投影只由相机给:世界 → 裁剪就是相机的 view × projection,世界 z 走真深度(透视档近大远小)
        push_constants = {};
        const std::array<float, 16> mvp = to_float16(camera.view_projection());
        std::memcpy(push_constants.mvp, mvp.data(), sizeof(push_constants.mvp));
        push_constants.screen_w = static_cast<float>(frame_extent.width);
        push_constants.screen_h = static_cast<float>(frame_extent.height);
        push_constants.snap_pixel = snap_pixel ? 1.0f : 0.0f;

        vertex_count = static_cast<uint32_t>(vertex.size());
        vertex.clear();   // 本帧顶点已交给 GPU,列表清空等下一帧追加
    }
}
