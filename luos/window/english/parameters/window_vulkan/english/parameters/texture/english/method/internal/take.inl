namespace Gnik_luos {
    Texture_slot& Vulkan_texture::take(const std::string& key, double block_width, double block_height, const Information_image* passed) {
        if (block_stale(key, block_width, block_height)) {
            slot.erase(key);              // 过期的生成块:GPU 贴图与描述符一起放掉
            image_cache.forget(key);      // 旧像素也别再被 find 命中
            create_block(key, block_width, block_height);
        }
        auto it = slot.find(key);
        if (it != slot.end()) {
            return it->second;   // 槽位按块缓存:一块一个槽位
        }

        Texture_slot created{};
        static const unsigned char solid[4]{102, 102, 102, 255};   // 库内那张 0.4 纯色(1×1)
        if (passed != nullptr && passed->data != nullptr) {
            create_slot(created, passed->data, static_cast<uint32_t>(passed->width), static_cast<uint32_t>(passed->height));
        } else if (key.empty()) {
            create_slot(created, solid, 1, 1);   // 键为空:就是库内这张纯色
        } else if (key.find(':') != std::string::npos) {
            // 键里带冒号 = 直接交过来的像素(图片、字体图集):没给像素是调用方出了错,报一行、退回纯色,不当场抛
            std::cerr << "直接交的像素缺失,已退回纯色: " << key << std::endl;
            create_slot(created, solid, 1, 1);
        } else {
            int file_width = 0;
            int file_height = 0;
            const bool usable = std::filesystem::exists(key)
                && stbi_info(key.c_str(), &file_width, &file_height, nullptr) != 0;   // 先问文件能不能读,不拿异常当判据
            if (!usable) {
                // 这一块没有(或解不开):按它自己的尺寸生成一张描边块,本次就用它;同一个文件夹只报一次
                const size_t slash = key.find_last_of('/');
                const std::string folder = slash == std::string::npos ? key : key.substr(0, slash);
                if (reported.insert(folder).second) {
                    std::cerr << "贴图块缺失,已按描边生成: " << folder << std::endl;
                }
                create_block(key, block_width, block_height);
            }
            const Information_image& image = image_cache.find(key);
            create_slot(created, image.data, static_cast<uint32_t>(image.width), static_cast<uint32_t>(image.height));
        }
        return slot.emplace(key, std::move(created)).first->second;
    }
}
