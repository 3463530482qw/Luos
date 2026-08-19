namespace Gnik_luos {
    class Json {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
        public:
            Json();
            ~Json();
    };
    using 配置文件 = Json;
}
#include "english/add.inl"
#include "english/remove.inl"
#include "english/clear.inl"
#include "english/get.inl"
#include "main.inl"