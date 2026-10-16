namespace Gnik_luos {
    // 清单里记着、而现算尺寸与记的不符 = 这块生成物过期了,要重画;
    // 清单里没有 = 手画的素材,永不覆盖;文件已被换成手画的(像素尺寸对不上)就从清单里划掉
    bool Vulkan_texture::block_stale(const std::string& path, double block_width, double block_height) {
        if (path.empty() || path.find(':') != std::string::npos) {
            return false;   // 键里带冒号 = 直接交的像素(图片或字体图集):不是磁盘上的生成块
        }
        const size_t slash = path.find_last_of('/');
        if (slash == std::string::npos) {
            return false;
        }
        const std::string folder = path.substr(0, slash);
        read_blocks(folder);
        auto it = generated.find(path);
        if (it == generated.end()) {
            return false;
        }
        if (it->second.first == block_width && it->second.second == block_height) {
            return false;
        }
        int file_width = 0;
        int file_height = 0;
        if (!stbi_info(path.c_str(), &file_width, &file_height, nullptr)
            || std::abs(file_width - it->second.first * 2.0) > 1.0
            || std::abs(file_height - it->second.second * 2.0) > 1.0) {
            generated.erase(it);
            write_blocks(path);
            return false;
        }
        if (reported.insert(folder).second) {
            std::cerr << "贴图块尺寸不符,已按描边重画: " << folder << std::endl;
        }
        return true;
    }
}
