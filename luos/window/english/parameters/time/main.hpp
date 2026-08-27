namespace Gnik_luos {
    class Window_time {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
        private:
            #include "english/available/internal/function.inl"
        public:
            Window_time();
            ~Window_time();
    };
    using 窗口时间 = Window_time;
}
#include "english/load.inl"
#include "english/time.inl"
#include "english/youklx_frame_time.inl"
#include "english/sleep.inl"
#include "english/router.inl"
#include "english/update.inl"
#include "main.inl"