namespace Gnik_luos {
    void Vulkan_line_render::destroy() {
        pipeline = nullptr;
        pipeline_layout = nullptr;
        vertex_buffer = {nullptr, nullptr};
        vertex_memory = {nullptr, nullptr};
        vertex_capacity = 0;
        vertex_count = 0;
        vertex_frame = 0;
        vertex.clear();
        vulkan = nullptr;
    }
}
