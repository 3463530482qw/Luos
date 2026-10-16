namespace Gnik_luos {
    // 一个字号一张图集:互不打扰 —— 某个字号长出新字形,不会把别的字号已经算好的 uv 弄失效
    struct Atlas_info {
        std::vector<unsigned char> pixels{};             // RGBA:字形覆盖率写在 alpha(着色器取贴图 alpha × 顶点色)
        int width{0};                                    // 图集宽(2 的幂):按字体的字形上界定,定下来很少再变
        int height{0};                                   // 图集高:放不下就翻倍重建
        int cursor_x{0}, cursor_y{0}, row_height{0};     // 行式打包的游标与当前行高
        bool need_wider{false};                          // 上一次没放下是因为行宽不够(要同时长宽,只长高会原地打转)
        double pixel_height{0.0};                        // 这张图集是按哪个字号烤的(重建时要用它重烤)
        std::vector<char32_t> glyph_order{};             // 已经烤过的码位(重建时按这个顺序重烤)
        std::map<char32_t, Glyph> glyph{};               // 这个字号已经烤好的字形
        uint64_t revision{0};                            // 内容版本:每次往像素里写字形都 +1(渲染侧按"字体+版本"认贴图槽位,不靠像素地址)
        std::mutex guard{};                              // 烤字形可能跨线程,图集改动一律在里面
    };
}
