#include "english/parameters/keyval.inl"
namespace Gnik_luos {
    class Key_board {
        public:
            #include "english/available/function.inl"
            //#include "中文/可用/函数.inl"
        private:
            #include "english/available/internal/variable.inl"
        public:
    };
    using 键盘 = Key_board;
}
#include "english/press.inl"
//#include "english/hold.inl"
//#include "english/release.inl"
#include "english/update.inl"