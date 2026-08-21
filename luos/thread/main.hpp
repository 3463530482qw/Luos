#include "english/parameters/phase.inl"
namespace Gnik_luos {
    class Thread {
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
        private:
            #include "english/available/internal/function.inl"
        public:
            Thread();
            ~Thread();
    };
    using 线程 = Thread;
}
#include "english/pack.inl"
#include "english/run.inl"
#include "english/clear.inl"
#include "english/wait.inl"
#include "main.inl"