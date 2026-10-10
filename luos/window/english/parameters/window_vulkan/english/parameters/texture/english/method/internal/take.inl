namespace Gnik_luos {
    Texture_slot& Vulkan_texture::take(const std::string& path, const std::vector<Line_span>& usage) {
        auto it = slot.find(path);
        if (it != slot.end()) {
            return it->second;
        }

        // 展开图的世界尺寸:宽 = 同一路径里最长那条命令的总长,高 = 六行按面的真实尺寸拼出来的总和
        double world_width = 0.0;
        double world_height = 0.0;
        for (const Line_span& item : usage) {
            if (item.length > world_width) {
                world_width = item.length;
                world_height = item.size_x * 2.0 + item.size_y * 4.0;
            }
        }
        if (world_width <= 0.0) {
            world_width = 1.0;
        }
        if (world_height <= 0.0) {
            world_height = 1.0;
        }

        Texture_slot created{};
        created.world_width = world_width;
        created.world_height = world_height;
        if (path.empty()) {
            static const unsigned char solid[4]{102, 102, 102, 255};   // 路径为空:库内那张 0.4 纯色(1×1)
            create_slot(created, solid, 1, 1);
        } else {
            try {
                const Information_image& image = image_cache.find(path);
                create_slot(created, image.data, static_cast<uint32_t>(image.width), static_cast<uint32_t>(image.height));
            } catch (const std::runtime_error&) {
                // 路径下没有图(或解不开):不当错误,生成一张带线条 uv 范围的提示图,本次就用它
                create_guide(path, usage);
                const Information_image& image = image_cache.find(path);
                create_slot(created, image.data, static_cast<uint32_t>(image.width), static_cast<uint32_t>(image.height));
            }
        }
        return slot.emplace(path, std::move(created)).first->second;
    }

    const Texture_slot& Vulkan_texture::slot_of(const std::string& path) {
        auto it = slot.find(path);
        if (it == slot.end()) {
            throw std::runtime_error("Vulkan_texture::slot_of => No slot for this path: " + path);
        }
        return it->second;
    }
}
