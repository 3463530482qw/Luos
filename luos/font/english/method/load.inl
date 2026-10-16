namespace Gnik_luos {
    // 读一份 ttf/otf:整份字节留在本对象里(stb_truetype 的解析结果一直指着它),再交给 stb 解析
    Font& Font::load(const std::string& path) {
        std::ifstream stream(path, std::ios::binary | std::ios::ate);
        if (!stream.is_open()) {
            throw std::runtime_error("Font::load => Font file cannot be opened: " + path);
        }
        const std::streamsize size = stream.tellg();
        stream.seekg(0, std::ios::beg);
        file_data.resize(static_cast<size_t>(size));
        if (size > 0 && !stream.read(reinterpret_cast<char*>(file_data.data()), size)) {
            throw std::runtime_error("Font::load => Font file cannot be read: " + path);
        }
        name = path;
        atlas_map.clear();   // 换了字体:旧字号图集是旧字形的
        private_load();
        return *this;
    }
}
