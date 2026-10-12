namespace Gnik_luos {
    // 把该块所在文件夹的清单整份重写(只写这个文件夹自己的那些块)
    void Vulkan_texture::write_blocks(const std::string& path) {
        const size_t slash = path.find_last_of('/');
        if (slash == std::string::npos) {
            return;
        }
        const std::string folder = path.substr(0, slash);
        blocks_read.insert(folder);
        std::ofstream file(folder + "/blocks.txt", std::ios::trunc);
        for (const auto& entry : generated) {
            if (entry.first.rfind(folder + "/", 0) != 0) {
                continue;
            }
            file << entry.first.substr(folder.size() + 1) << " " << entry.second.first << " " << entry.second.second << "\n";
        }
    }
}
