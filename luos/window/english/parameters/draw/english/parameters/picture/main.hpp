namespace Gnik_luos {
    class Picture {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
            #include "english/available/internal/function.inl"
    };
    using 图片绘制 = Picture;
}
//链式设置
#include "english/from.inl"
#include "english/to.inl"
#include "english/rotation.inl"
#include "english/rotation_point.inl"
#include "english/rgba.inl"
#include "english/corner_rgba.inl"
#include "english/texture.inl"
//几何
#include "english/update.inl"
#include "english/internal/private_rotate.inl"
#include "english/internal/private_rotate_vector.inl"
#include "english/internal/private_quad.inl"
//json 加载
#include "english/batch_load.inl"
//对外查询
#include "english/vertex.inl"
