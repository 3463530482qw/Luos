namespace Gnik_luos {
    void Font::private_load() {
        if (file_data.empty()) {
            throw std::runtime_error("Font::load => Font data is empty: " + name);
        }
        if (stbtt_InitFont(&font_info, file_data.data(), 0) == 0) {
            throw std::runtime_error("Font::load => Font cannot be parsed: " + name);
        }
        stbtt_GetFontVMetrics(&font_info, &ascent_metric, &descent_metric, &line_gap_metric);
        ready = true;
    }
}
