#include "english/parameters/vertex.inl"
#include "english/parameters/line/main.hpp"
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
#include "english/method/line.inl"
#include "english/method/draw.inl"
