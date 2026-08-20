namespace Gnik_luos {
    class Scene {
        public:
            #include "english/available/variable.inl"
            #include "中文/可用/变量.inl"
        public:
            #include "english/available/function.inl"
            #include "中文/可用/函数.inl"
        private:
            #include "english/available/internal/variable.inl"
        public:
            ~Scene();
    };
    using 场景 = Scene;
}
#include "english/load.inl"
#include "english/remove.inl"
#include "english/clear.inl"
#include "main.inl"