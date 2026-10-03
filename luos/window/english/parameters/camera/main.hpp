#include "english/parameters/constant.inl"
#include "english/parameters/rotation_basis.inl"
namespace Gnik_luos {
    class Camera {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/internal/variable.inl"
        private:
            #include "english/internal/function.inl"
    };
}
#include "english/method/available/canvas_rect.inl"
#include "english/method/available/canvas_clip_matrix.inl"
#include "english/method/available/apply_default.inl"
#include "english/method/available/rect.inl"
#include "english/method/available/view_matrix.inl"
#include "english/method/available/projection_view_space.inl"
#include "english/method/available/view_projection.inl"
#include "english/method/available/ray_through_screen.inl"
#include "english/method/available/canvas_from_screen.inl"
#include "english/method/available/world_from_screen.inl"
#include "english/method/available/canvas_uv.inl"
#include "english/method/internal/aspect.inl"
#include "english/method/internal/rotation_basis.inl"
#include "english/method/internal/view_origin.inl"
#include "english/method/internal/view_direction.inl"
#include "english/method/internal/perspective_matrix.inl"
#include "english/method/internal/orthographic_matrix.inl"
#include "english/method/internal/fit_distance.inl"
