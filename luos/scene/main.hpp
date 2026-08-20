namespace Gnik_luos {
    class Scene {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
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