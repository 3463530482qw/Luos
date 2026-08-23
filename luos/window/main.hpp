#include "english/parameters/windowinfo/main.hpp"
namespace Gnik_luos {
    class Window {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
    };
    using 窗口 = Window;
}
#include "english/setting/setting.inl"