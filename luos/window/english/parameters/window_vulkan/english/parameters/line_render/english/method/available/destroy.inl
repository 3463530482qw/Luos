namespace Gnik_luos {
    void Vulkan_line_render::destroy() {
        pipeline = nullptr;
        pipeline_layout = nullptr;
        descriptor_set = nullptr;   // 集先放,池后放:集的释放要靠池还在
        descriptor_pool = nullptr;
        descriptor_layout = nullptr;
        texture_sampler = nullptr;
        texture_view = nullptr;
        texture_image = nullptr;
        texture_memory = nullptr;
        texture_ready = false;
        vertex_buffer = {nullptr, nullptr};
        vertex_memory = {nullptr, nullptr};
        vertex_capacity = 0;
        vertex_count = 0;
        vertex_frame = 0;
        vertex.clear();
    }
}
