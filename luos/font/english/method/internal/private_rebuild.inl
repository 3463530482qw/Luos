namespace Gnik_luos {
    // 换一张更大的图集:旧字形按烤过的顺序重烤一遍,新像素换给调用方
    // 旧图集对象不销毁(谁还拿着它算好的 uv 就谁拿着),所以别的命令手上的字形不会指到空处
    // 行宽与行高一起长:光是"更高的图集"救不了比行宽还宽的字形(那样每次重烤都在同一处卡住,递归到栈溢出)
    void Font::private_rebuild(std::shared_ptr<Atlas_info>& target) {
        if (target == nullptr) {
            throw std::runtime_error("Font::private_rebuild => No atlas to rebuild");
        }
        const bool wider = target->need_wider;
        const std::vector<char32_t> order = target->glyph_order;
        const int width = wider ? target->width * 2 : target->width;
        const int height = target->height * 2;
        if (static_cast<int64_t>(width) * static_cast<int64_t>(height) > static_cast<int64_t>(atlas_pixel_limit)) {
            throw std::runtime_error("Font::private_rebuild => Font atlas is too large: " + name);
        }

        std::shared_ptr<Atlas_info> grown = std::make_shared<Atlas_info>();
        grown->pixel_height = target->pixel_height;
        grown->width = width;
        grown->height = height;
        grown->pixels.assign(static_cast<size_t>(width) * static_cast<size_t>(height) * 4, 0);   // 先备好像素表:重烤要往里写
        target = grown;   // 先换上去:重烤拿到的就是新对象(烤进去的字形由 private_bake 记进新图集)

        const double scale = private_scale(grown->pixel_height);
        for (char32_t codepoint : order) {
            grown->glyph_order.push_back(codepoint);
            int advance = 0;
            int bearing = 0;
            stbtt_GetCodepointHMetrics(&font_info, static_cast<int>(codepoint), &advance, &bearing);
            private_bake(grown, codepoint, scale, static_cast<float>(static_cast<double>(advance) * scale));
        }
    }
}
