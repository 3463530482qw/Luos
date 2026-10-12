namespace Gnik_luos {
    Texture_slot& Vulkan_texture::take(const std::string& key, double block_width, double block_height, const Information_image* passed) {
        auto it = slot.find(key);
        if (it != slot.end()) {
            return it->second;   // 槽位按块缓存:一块一个槽位
        }

        Texture_slot created{};
        if (passed != nullptr && passed->data != nullptr) {
            create_slot(created, passed->data, static_cast<uint32_t>(passed->width), static_cast<uint32_t>(passed->height));
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
