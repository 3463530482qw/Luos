namespace Gnik_luos {
    void Vulkan_line_render::create_pipeline(const vk::raii::RenderPass& render_pass) {
        std::vector<uint32_t> vertex_code = load_shader(vertex_shader_file.c_str());
        std::vector<uint32_t> fragment_code = load_shader(fragment_shader_file.c_str());

        vk::ShaderModuleCreateInfo vertex_info;
        vertex_info.setCodeSize(vertex_code.size() * sizeof(uint32_t));
        vertex_info.setPCode(vertex_code.data());
        vk::raii::ShaderModule vertex_shader((*vulkan)->device, vertex_info);
    }
}