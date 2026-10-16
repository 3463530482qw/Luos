Font& load(const std::string& path);   // 读一份 ttf/otf:重复加载同一份会从头来过(图集与度量一起换)
Glyph glyph(char32_t codepoint, double pixel_height);   // 取这个字号下的字形:没烤过就现烤,字体没有这个码位给空字形
std::shared_ptr<const Atlas_info> atlas(double pixel_height) const;   // 这个字号当前的图集(没烤过这个字号就给空)
double ascent(double pixel_height) const;               // 基线到文字块顶的像素高
double line_height(double pixel_height) const;          // 字体自己的行高(上下伸部加行距)
