#include "english/parameters/glyph_texture_key.inl"
#include "english/parameters/vertex.inl"
#include "english/parameters/line_span.inl"
#include "english/parameters/sprite_sheet.inl"
#include "english/parameters/reader/main.hpp"
#include "english/parameters/text/main.hpp"
#include "english/parameters/tilemap/main.hpp"
#include "english/parameters/line/main.hpp"
#include "english/parameters/picture/main.hpp"
namespace Gnik_luos {
    class Draw {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
    };
    using 绘制 = Draw;
}
#include "english/method/bind_vertex_sink.inl"
#include "english/method/bind_span_sink.inl"
#include "english/method/line.inl"
#include "english/method/picture.inl"
#include "english/method/text.inl"
#include "english/method/tilemap.inl"
#include "english/method/draw.inl"
