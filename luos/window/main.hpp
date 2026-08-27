#include "english/parameters/windowinfo/main.hpp"
#include "english/parameters/create_info/main.hpp"
#include "english/parameters/time/main.hpp"
#include "english/parameters/mouse/main.hpp"
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
    };
    using 窗口 = Window;
}
#include "english/position_adjustment/main.inl"
#include "english/resize.inl"
#include "english/setting/setting.inl"
#include "english/create.inl"
#include "english/mouse_update.inl"
#include "english/run.inl"
#include "english/close.inl"