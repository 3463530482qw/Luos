namespace Gnik_luos {
    class Line {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
            #include "english/available/internal/function.inl"
    };
    using 线 = Line;
}
#include "english/line_empty.inl"
//路由装配:按脏标记定步骤,update 顺次跑步骤出顶点
#include "english/internal/router.inl"
#include "english/internal/update.inl"
#include "english/internal/run.inl"
#include "english/internal/private_direction.inl"
#include "english/internal/private_quad.inl"
#include "english/internal/private_rgba.inl"
//链式设置
#include "english/from.inl"
#include "english/to.inl"
#include "english/width.inl"
#include "english/rgba.inl"
//对外查询
#include "english/vertex.inl"