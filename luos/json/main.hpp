#include "english\parameters\json_reader.inl"
namespace Gnik_luos {
    class Json {
        public:
            #include "english/api/var.inl"
        public:
            #include "english/api/function.inl"
        public:
            ~Json() { clear(); };
    };
    using 配置文件 = Json;
}
#include "english/add.inl"
#include "english/remove.inl"
#include "english/clear.inl"
#include "english/get.inl"