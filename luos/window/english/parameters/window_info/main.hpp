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
            bool private_load_camera();   // 读 window_info 里的相机子段;没有这一段就返回 false
    };
    using 窗口配置信息 = Window_settings_info;
}
#include "english/private_load_camera.inl"
#include "english/load.inl"
