namespace Gnik_luos {
    std::vector<uint32_t> Vulkan_ground::load_shader(const char* name) {
        std::string path = std::string("shaders/") + name;
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            throw std::runtime_error(std::string("Vulkan_ground::load_shader => Cannot open shader: ") + path);
        }
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<uint32_t> code(static_cast<size_t>(size) / sizeof(uint32_t));
        file.read(reinterpret_cast<char*>(code.data()), size);
        return code;
    }
}
