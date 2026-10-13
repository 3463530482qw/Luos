namespace Gnik_luos {
    void Vulkan_line_render::prepare() {
        vertex_count = 0;
        group_texture.clear();
        group_descriptor.clear();
        group_range.clear();
        if (pipeline == nullptr || vertex.empty()) {
            vertex.clear();
            span.clear();
            return;
        }

        // 每个"段 × 面"一块贴图:逐段按留下的面走,顶点游标顺次推进(连接处那两个端面不在里面)
        for (const Line_span& item : span) {
            size_t cursor = item.begin;
            for (size_t segment = 0; segment < item.segment.size(); segment++) {
                const uint8_t mask = segment < item.face_mask.size() ? item.face_mask[segment] : 0x3F;
                for (size_t face = 0; face < 6; face++) {
                    if ((mask & (1 << face)) == 0) {
                        continue;
                    }
                    const bool end_face = face < 2;                                   // 面序:起端面 / 终端面 / +x / -x / +y / -y
                    const bool across_is_y = !end_face && face < 4;                   // 侧面里 +x / -x 跨局部 y,其余跨局部 x
                    const double block_width = end_face ? item.size_x : item.segment[segment];
                    const double block_height = end_face ? item.size_y : (across_is_y ? item.size_y : item.size_x);
                    const bool direct = item.image.data != nullptr;                   // 直接交的像素:所有块共用这一张
                    std::string key{};
                    if (direct) {
                        key = item.texture_key;
                    } else if (!item.texture_key.empty()) {
                        key = item.texture_key + "/" + texture_block_name(segment, face) + ".png";
                    }
                    group_texture.push_back(key);
                    group_descriptor.push_back(*texture().descriptor(key, block_width, block_height, direct ? &item.image : nullptr));
                    group_range.push_back({static_cast<uint32_t>(cursor), 6});
                    cursor += 6;
                }
            }
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
