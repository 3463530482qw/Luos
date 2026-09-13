#include "english/parameters/view_rect.inl"
namespace Gnik_luos {
    class Camera {
        public:
            float x{0.0f}, y{0.0f};                              // 相机中心(世界/画布坐标)
            float zoom{1.0f};
            float canvas_width{1600.0f}, canvas_height{900.0f};   // 视口对应的画布尺寸
        public:
            #include "english/available/function.inl"
    };
}
#include "english/view.inl"
