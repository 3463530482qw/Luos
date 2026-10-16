int private_power_of_two(int value);   // 取不小于 value 的 2 的幂(下限 2)
double private_scale(double pixel_height) const;   // 字号 → stb_truetype 的缩放系数(按字高定)
void private_load();                               // 把 file_data 交给 stb_truetype 并取度量
int private_glyph_bound(double scale) const;        // 字形上界(像素):行宽按它定
std::array<int, 4> private_pad(int width, int height);   // 位图补成 2 的幂正方形:回空隙四边
bool private_place(Atlas_info& target, const unsigned char* bitmap, int width, int height, Glyph& metric);   // 放进图集并填 uv;回 false = 这块放不下
Glyph private_bake(std::shared_ptr<Atlas_info>& target, char32_t codepoint, double scale, float advance);   // 烤一个字形(放不下会重建图集再来)
void private_rebuild(std::shared_ptr<Atlas_info>& target);   // 换更大的图集重来(宽字形同时长宽),旧字形按序重烤
