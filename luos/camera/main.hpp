#include "english/parameters/view_rect.inl"
#include "english/parameters/matrix4.inl"
#include "english/parameters/rotation_basis.inl"
namespace Gnik_luos {
    class Camera {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/function.inl"
    };
}
#include "english/method/available/view.inl"
#include "english/method/available/view_projection.inl"
#include "english/method/internal/rotation_basis.inl"
#include "english/method/internal/view_matrix.inl"
#include "english/method/internal/perspective_matrix.inl"
#include "english/method/internal/orthographic_matrix.inl"
#include "english/method/internal/multiply.inl"
