namespace Gnik_luos {
    // 贴图文件夹里那份 blocks.txt:一行一块"块名 宽 高",只记生成过的块
    void Vulkan_texture::read_blocks(const std::string& folder) {
        if (!blocks_read.insert(folder).second) {
            return;
        }
        std::ifstream file(folder + "/blocks.txt");
        std::string name;
        double block_width = 0.0;
        double block_height = 0.0;
        while (file >> name >> block_width >> block_height) {
            generated[folder + "/" + name] = {block_width, block_height};
        }
    }
}
