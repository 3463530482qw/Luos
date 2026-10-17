#include "english/parameters/angle.inl"
namespace Gnik_luos {
    class Font;   // 字体只按引用用(正向声明即可):没绑字体的文字命令改画默认字形贴图
    class Text {   // 文字命令:绑定一份字体,按字号逐字形摊成四边形;没绑字体就按字号排默认贴图方块
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
            #include "english/available/internal/function.inl"
    };
    using 文字 = Text;
}
//链式设置
#include "english/from.inl"
#include "english/size.inl"
#include "english/align.inl"
#include "english/rotation.inl"
#include "english/rgba.inl"
//路由装配:按脏标记定步骤,update 顺次跑步骤出顶点
#include "english/internal/router.inl"
#include "english/internal/run.inl"
//几何
#include "english/update.inl"
#include "english/internal/private_rotate.inl"
#include "english/internal/private_utf8.inl"
#include "english/internal/private_measure.inl"
#include "english/internal/private_align_offset.inl"
#include "english/internal/private_emit.inl"
#include "english/internal/private_layout.inl"
//json 加载
#include "english/batch_load.inl"
//对外查询
#include "english/vertex.inl"
