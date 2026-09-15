namespace Gnik_luos {
    std::vector<uint32_t> Vulkan_line_render::load_shader(const char* name) {
        // 兼容两种运行目录:根目录(build/shaders/)与 build/(shaders/)
        std::array<std::string, 2> candidates{std::string("build/shaders/") + name, std::string("shaders/") + name};
        for (const std::string& path : candidates) {
            std::ifstream file(path, std::ios::binary | std::ios::ate);
            if (!file.is_open()) {
                continue;
            }
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);
            std::vector<uint32_t> code(static_cast<size_t>(size) / sizeof(uint32_t));
            file.read(reinterpret_cast<char*>(code.data()), size);
            return code;
        }
        throw std::runtime_error(std::string("Vulkan_line_render::load_shader => Cannot open shader: ") + name);
    }
}
