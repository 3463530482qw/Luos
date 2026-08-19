namespace Gnik_luos {
    class Json {
        public:
            #include "english/api/var.inl"
        public:
            #include "english/api/function.inl"
        private:
            #include "english/api/internal/var.inl"
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