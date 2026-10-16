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
        if (passed != nullptr && passed->data != nullptr) {
            create_slot(created, passed->data, static_cast<uint32_t>(passed->width), static_cast<uint32_t>(passed->height));
        } else if (key.find(':') != std::string::npos) {
            // 键里带冒号 = 直接交过来的像素(已经加载好的图片、字体的图集):没有像素就是调用方出了错,不在这里猜文件路径
            throw std::runtime_error("Vulkan_texture::take => Direct pixels are missing for key: " + key);
        } else if (key.empty()) {
            static const unsigned char solid[4]{102, 102, 102, 255};   // 键为空:库内那张 0.4 纯色(1×1)
            create_slot(created, solid, 1, 1);
        } else {
            try {
                const Information_image& image = image_cache.find(key);
                create_slot(created, image.data, static_cast<uint32_t>(image.width), static_cast<uint32_t>(image.height));
            } catch (const std::runtime_error&) {
                // 这一块没有(或解不开):按它自己的尺寸生成一张描边块,本次就用它;同一个文件夹只报一次
                const size_t slash = key.find_last_of('/');
                const std::string folder = slash == std::string::npos ? key : key.substr(0, slash);
                if (reported.insert(folder).second) {
                    std::cerr << "贴图块缺失,已按描边生成: " << folder << std::endl;
                }
                create_block(key, block_width, block_height);
                const Information_image& image = image_cache.find(key);
                create_slot(created, image.data, static_cast<uint32_t>(image.width), static_cast<uint32_t>(image.height));
            }
        }
        return slot.emplace(key, std::move(created)).first->second;
    }
}
