namespace Gnik_luos {
    // 取字形:这个字号没烤过就现烤一个,再回 uv 与度量。烤的过程会改图集,所以全程在字号的锁里
    Glyph Font::glyph(char32_t codepoint, double pixel_height) {
        if (!ready) {
            throw std::runtime_error("Font::glyph => No font loaded");
        }
        if (pixel_height <= 0.0) {
            return Glyph{};   // 字号不成立:不给形状,也不替它编一个
        }
        if (stbtt_FindGlyphIndex(&font_info, static_cast<int>(codepoint)) == 0) {
            return Glyph{};   // 这份字体没有这个码位:空字形,调用方按 0 前进量走
        }
        const double scale = private_scale(pixel_height);
        int advance = 0;
        int bearing = 0;
        stbtt_GetCodepointHMetrics(&font_info, static_cast<int>(codepoint), &advance, &bearing);
        Glyph blank{};
        blank.advance = static_cast<float>(static_cast<double>(advance) * scale);
        if (codepoint < 32) {
            return blank;   // 控制码:有前进量,没有位图
        }

        const auto found = atlas_map.find(pixel_height);
        std::shared_ptr<Atlas_info> target = nullptr;
        if (found == atlas_map.end()) {
            if (atlas_map.size() >= font_size_limit) {
                throw std::runtime_error("Font::glyph => Too many sizes on one font: " + name);
            }
            target = std::make_shared<Atlas_info>();
            target->pixel_height = pixel_height;
            atlas_map[pixel_height] = target;
        } else {
            target = found->second;
        }

        std::lock_guard<std::mutex> lock(target->guard);
        const auto cached = target->glyph.find(codepoint);
        if (cached != target->glyph.end()) {
            return cached->second;
        }
        Glyph baked = private_bake(target, codepoint, scale, blank.advance);
        if (baked.width <= 0.0f || baked.height <= 0.0f) {
            return blank;   // 空白字符(空格这类):有前进量,没有位图
        }
        target->glyph_order.push_back(codepoint);
        target->glyph.emplace(codepoint, baked);
        return baked;
    }
}
