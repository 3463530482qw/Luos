namespace Gnik_luos {
    void Text::update() {
        const bool placeholder = face == nullptr;   // 没绑字体:改画默认字形贴图(不是不出顶点)
        if (!dirty) {
            if (placeholder) {
                return;   // 占位那一档没有"字体图集被别人改了"这回事:排一次就够
            }
            const std::shared_ptr<const Atlas_info> current = face->atlas(static_cast<double>(font_size));
            if (current == nullptr || current->revision == texture_revision) {
                return;   // 参数没动、图集也没被别的命令改动:顶点与贴图都还是上一次那份
            }
            dirty = true;   // 图集内容变了(有新字形烤进去):手上的 uv 与像素都过期了,重排
        }
        cache.clear();
        if (content.empty() || font_size <= 0.0f) {
            dirty = false;
            return;   // 没写文字、字号不成立:这条命令不出顶点(库里不替它编一段默认文字)
        }

        if (placeholder) {
            // 贴图边长按"一个方块会有多少像素"取 2 的幂:放大后的毛刺最少
            const double box_pixels = std::max(static_cast<double>(font_size), static_cast<double>(font_size) * font_default_texture_advance);
            int side = static_cast<int>(std::ceil(std::log2(std::max(box_pixels, 1.0))));
            side = 1 << std::clamp(side, 1, 9);
            if (texture_pixels.data == nullptr || texture_pixels.width != side) {
                // 只在边长真的变了才重造:每帧重造会让贴图槽位一直新建
                texture_pixels = Information_image_default_font(side);
                texture_pixels.data = texture_pixels.pixels.data();
            }
            texture_key = glyph_texture_key(texture_pixels);
        } else {
            const size_t existing = face->atlas_map.size();
            if (face->atlas(static_cast<double>(font_size)) == nullptr && existing >= font_size_limit) {
                throw std::runtime_error("Text::update => Too many sizes on one font");
            }
        }

        private_rotate();
        cache.reserve(static_cast<size_t>(private_line_count()) * 6);
        private_layout();

        if (!placeholder) {
            const std::shared_ptr<const Atlas_info> current = face->atlas(static_cast<double>(font_size));
            texture_pixels = Information_image{};
            if (current != nullptr && !current->pixels.empty()) {
                texture_pixels.data = const_cast<unsigned char*>(current->pixels.data());   // 这份图集:渲染侧本帧读一次
                texture_pixels.width = current->width;
                texture_pixels.height = current->height;
                texture_pixels.channels = 4;
            }
            texture_revision = current == nullptr ? 0 : current->revision;
            texture_key = glyph_texture_key(texture_pixels);
        }
        dirty = false;
    }
}
