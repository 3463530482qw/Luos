#include "english/parameters/window_info/main.hpp"
#include "english/parameters/create_info/main.hpp"
#include "english/parameters/time/main.hpp"
#include "english/parameters/mouse/main.hpp"
#include "english/parameters/key_board/main.hpp"
#include "english/parameters/window_vulkan/main.hpp"
namespace Gnik_luos {
    class Window {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
            #include "中文/可用/函数.inl"
        private:
            #include "english/available/internal/variable.inl"
        private:
            #include "english/available/internal/function.inl"
        public:
            Window();
            ~Window();
    };
    using 窗口 = Window;
}
// initialize 需要 Window 完整定义(参数全部取自宿主窗口),故在 Window 之后引入
#include "english/parameters/window_vulkan/english/initialize.inl"
#include "english/position_adjustment/main.inl"
#include "english/resize.inl"
#include "english/setting/setting.inl"
#include "english/create.inl"
#include "english/bind_window.inl"
#include "english/mouse_update.inl"
#include "english/window_resize.inl"
#include "english/icon.inl"
#include "english/run.inl"
#include "english/close.inl"
#include "main.inl"