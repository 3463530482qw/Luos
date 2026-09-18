namespace Gnik_luos {
    void Vulkan_line_render::create_pipeline(const vk::raii::RenderPass& render_pass) {
        std::vector<uint32_t> vertex_code = load_shader("line.vert.spv");
        std::vector<uint32_t> fragment_code = load_shader("line.frag.spv");
    }
}