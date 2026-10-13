#include "english/parameters/angle.inl"
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
//路由装配:按脏标记定步骤,update 顺次跑步骤出顶点
#include "english/internal/router.inl"
#include "english/internal/update.inl"
#include "english/internal/run.inl"
#include "english/internal/private_build_frame.inl"
#include "english/internal/private_miter.inl"
#include "english/internal/private_rotate.inl"
#include "english/internal/private_rotate_vector.inl"
#include "english/internal/private_box.inl"
#include "english/internal/private_rgba.inl"
#include "english/internal/private_read_point.inl"
#include "english/internal/private_read_size.inl"
#include "english/internal/private_read_rotation_point.inl"
#include "english/internal/private_read_rotation.inl"
#include "english/internal/private_read_rgba.inl"
#include "english/internal/private_read_texture.inl"
#include "english/internal/private_read_texture_path.inl"
#include "english/internal/private_read_seal.inl"
//链式设置
#include "english/from.inl"
#include "english/to.inl"
#include "english/size.inl"
#include "english/rotation_point.inl"
#include "english/rotation.inl"
#include "english/rgba.inl"
#include "english/texture.inl"
#include "english/seal.inl"
//json 加载
#include "english/batch_load.inl"
//对外查询
#include "english/vertex.inl"
#include "english/segment_length.inl"
#include "english/face_mask.inl"
