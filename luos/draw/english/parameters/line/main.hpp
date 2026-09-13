#include "english/parameters/line_cmd_label/main.hpp"
#include "english/parameters/line_point.inl"
#include "../vertex.inl"
namespace Gnik_luos {
    class Draw_line_cmd {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
        private:
            #include "english/available/internal/function.inl"
    };
}
//几何主干:路由挑管线,update 跑一整条路径,段与段之间靠 private_segment 串起来
#include "english/internal/router.inl"
#include "english/internal/update.inl"
#include "english/internal/private_segment.inl"
#include "english/internal/private_segment_colors.inl"
#include "english/internal/private_endpoint.inl"
#include "english/internal/private_rotation.inl"
#include "english/internal/private_normal.inl"
#include "english/internal/private_connect.inl"
#include "english/internal/private_connect_miter.inl"
#include "english/internal/private_connect_round.inl"
//一段的几种出法:实线四边形、虚线、拐角圆角、端头封边、像素化
#include "english/internal/private_geometry.inl"
#include "english/internal/private_quad.inl"
#include "english/internal/private_dashed.inl"
#include "english/internal/private_edge_pick.inl"
#include "english/internal/private_edge_place.inl"
#include "english/internal/private_edge_cap.inl"
#include "english/internal/private_edge_triangle.inl"
#include "english/internal/private_pixel_col.inl"
#include "english/internal/private_pixel_rect.inl"
#include "english/internal/private_pixel_cells.inl"
//上色:渐变或平色,只染本段
#include "english/internal/private_gradient.inl"
#include "english/internal/private_single_color.inl"
//填充:内部/外部,取交点与梯形带的两套私有工具
#include "english/internal/private_fill_inside.inl"
#include "english/internal/private_fill_outside.inl"
#include "english/internal/private_band_spans.inl"
#include "english/internal/private_crossings.inl"
//以后接上:把路径本身的拐角切成圆弧(动的是中心线与填充,不是只动线条外角)
#include "english/internal/private_round_path.inl"
//对外查询
#include "english/vertex.inl"
#include "english/fill_vertex.inl"
//对外链式设置
#include "english/from.inl"
#include "english/to.inl"
#include "english/line_width.inl"
#include "english/color.inl"
#include "english/gradient.inl"
#include "english/dash.inl"
#include "english/solid.inl"
#include "english/connect.inl"
#include "english/pixelate.inl"
#include "english/smooth.inl"
#include "english/rotation.inl"
#include "english/end.inl"
#include "english/fill_inside.inl"
#include "english/fill_outside.inl"
#include "english/fill_above.inl"
#include "english/edge_rect.inl"
#include "english/edge_top.inl"
#include "english/edge_middle.inl"
#include "english/edge_bottom.inl"
#include "english/edge_both.inl"
#include "english/edge_round.inl"
#include "english/edge_round_notch.inl"
