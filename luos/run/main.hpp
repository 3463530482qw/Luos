namespace Gnik_luos {
    class Run {
        public:
            #include "english/available/function.inl"
            #include "中文/可用/函数.inl"
        private:
            #include "english/available/internal/variable.inl"
        private:
            #include "english/available/internal/function.inl"
        public:
            Run();
    };
    using 运行 = Run;
}
#include "english/scene.inl"
#include "english/thread.inl"
#include "english/start.inl"
#include "english/window.inl"
#include "english/router.inl"
#include "main.inl"