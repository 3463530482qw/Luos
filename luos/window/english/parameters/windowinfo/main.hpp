namespace Gnik_luos {
    class Window_settings_info {
        public:
            #include "english/available/variable.inl"
            #include "中文/可用/变量.inl"
        public:
            #include "english/available/function.inl"
            #include "中文/可用/函数.inl"
        private:
            #include "english/available/internal/variable.inl"
    };
    using 窗口配置信息 = Window_settings_info;
}
#include "english/load.inl"