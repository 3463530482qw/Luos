namespace Gnik_luos {
    // 烤一个字形:光栅化 → 补成 2 的幂正方形 → 放进图集
    // 图集放不下就换更大的重来一次;换过之后还放不下(字体没报准字形上界)就抛,绝不在原地打转
    Glyph Font::private_bake(std::shared_ptr<Atlas_info>& target, char32_t codepoint, double scale, float advance) {
        int width = 0;
        int height = 0;
        int offset_x = 0;
        int offset_y = 0;
        unsigned char* bitmap = stbtt_GetCodepointBitmap(
            &font_info,
            static_cast<float>(scale),
            static_cast<float>(scale),
            static_cast<int>(codepoint),
            &width,
            &height,
            &offset_x,
            &offset_y
        );
        Glyph metric{};
        metric.advance = advance;
        if (bitmap == nullptr || width <= 0 || height <= 0) {
            stbtt_FreeBitmap(bitmap, nullptr);
            return metric;   // 空白字形:只有前进量
        }

        // 最多两步:先按现图集放,放不下换更大的再放一次;两步都不成就是字形比图集上界还大
        for (int attempt = 0; attempt < 2; attempt++) {
            if (private_place(*target, bitmap, width, height, metric)) {
                stbtt_FreeBitmap(bitmap, nullptr);
                const std::array<int, 4> pad = private_pad(width, height);
                metric.offset_x = static_cast<float>(offset_x - pad[0]);
                metric.offset_y = static_cast<float>(offset_y - pad[1]);   // 基线以下的字形 offset_y 是负的:如实带出来
                return metric;
            }
            if (attempt == 0) {
                private_rebuild(target);
            }
        }
        stbtt_FreeBitmap(bitmap, nullptr);
        throw std::runtime_error("Font::private_bake => Glyph does not fit any atlas: " + name);
    }
}
