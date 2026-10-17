namespace Gnik_luos {
    // 路由:按脏标记装步骤(与 Line / Picture / Window 同一写法),分派在 run.inl。
    // 没绑字体那一档只装"默认字形贴图"的步骤;绑了字体则装"字号上限"检查这一步
    void Text::private_rebuild_route() {
        private_route.clear();
        if (content.empty() || font_size <= 0.0f) {
            return;   // 没写文字、字号不成立:这条命令不出顶点(库里不替它编一段默认文字)
        }
        const bool placeholder = face == nullptr;
        if (placeholder) {
            private_route.push_back([this]() {
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
            });
        } else {
            private_route.push_back([this]() {
                const size_t existing = face->atlas_map.size();
                if (face->atlas(static_cast<double>(font_size)) == nullptr && existing >= font_size_limit) {
                    throw std::runtime_error("Text::update => Too many sizes on one font");
                }
            });
        }
        private_route.push_back([this]() {
            private_rotate();   // 按三个角建旋转基
        });
        private_route.push_back([this]() {
            cache.reserve(static_cast<size_t>(private_line_count()) * 6);   // 顶点数 = 字形数 × 6,先按行数留个底
        });
        private_route.push_back([this]() {
            private_layout();   // 逐行逐字排:算位置、取字形、发顶点
        });
        if (!placeholder) {
            private_route.push_back([this]() {
                // 图集像素与键在这一步定死:绘制命令本帧末就被清掉,渲染侧不能事后再来取
                const std::shared_ptr<const Atlas_info> current = face->atlas(static_cast<double>(font_size));
                texture_pixels = Information_image{};
                if (current != nullptr && !current->pixels.empty()) {
                    texture_pixels.data = const_cast<unsigned char*>(current->pixels.data());
                    texture_pixels.width = current->width;
                    texture_pixels.height = current->height;
                    texture_pixels.channels = 4;
                }
                texture_revision = current == nullptr ? 0 : current->revision;
                texture_key = glyph_texture_key(texture_pixels);
            });
        }
    }
}
