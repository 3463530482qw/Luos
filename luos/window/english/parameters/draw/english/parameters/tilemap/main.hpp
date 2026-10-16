namespace Gnik_luos {
    class Tilemap {   // 地图图层命令:一整层瓦片画完只用一张贴图(贴图与所有绘制命令同一条管线)
        public:
            #include "english/available/variable.inl"
            Information_image texture_image{};   // 直接给的像素:渲染侧建槽时读一次(与图片命令同口径)
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
            #include "english/available/internal/function.inl"
    };
    using 地图 = Tilemap;
}
//链式设置(与图片/文字同风格:返回自身,drawer 收下这一帧就画)
#include "english/texture.inl"
#include "english/settings.inl"
//几何
#include "english/update.inl"
#include "english/internal/private_emit.inl"
#include "english/internal/private_layout.inl"
//对外查询
#include "english/vertex.inl"
