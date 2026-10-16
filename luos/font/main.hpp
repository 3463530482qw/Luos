#include "english/parameters/glyph.inl"
#include "english/parameters/atlas_info.inl"
#include "english/parameters/atlas_margin.inl"
#include "english/parameters/atlas_limit.inl"
#include "english/parameters/size_limit.inl"
#include "english/parameters/default_texture.inl"
namespace Gnik_luos {
    class Font {   // 字体模块:读一份 ttf,按字号把字形烤进自持图集,再把 uv 与度量交给绘制命令
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
            #include "english/available/internal/function.inl"
    };
    using 字体 = Font;
}
#include "english/method/load.inl"
#include "english/method/glyph.inl"
#include "english/method/atlas.inl"
#include "english/method/metrics.inl"
#include "english/method/information_image_default_font.inl"
#include "english/method/internal/private_power_of_two.inl"
#include "english/method/internal/private_scale.inl"
#include "english/method/internal/private_load.inl"
#include "english/method/internal/private_glyph_bound.inl"
#include "english/method/internal/private_pad.inl"
#include "english/method/internal/private_place.inl"
#include "english/method/internal/private_bake.inl"
#include "english/method/internal/private_rebuild.inl"
