#include "english/parameters/entry.inl"
namespace Gnik_luos {
    class Json {
        public:
            #include "english/available/function.inl"
            #include "中文/可用/函数.inl"
        private:
            #include "english/available/internal/variable.inl"
        public:
            ~Json();
    };
    using 配置文件 = Json;
}
#include "english/add.inl"
#include "english/remove.inl"
#include "english/clear.inl"
#include "english/get.inl"
#include "main.inl"