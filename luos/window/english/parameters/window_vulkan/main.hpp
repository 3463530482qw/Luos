#include "english/parameters/viewport/main.hpp"
#include "english/parameters/surface/main.hpp"
#include "english/parameters/command_pool/main.hpp"
namespace Gnik_luos {
    class Window_vulkan {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
            #include "english/available/internal/function.inl"
    };
}
#include "english/method/available/init.inl"
#include "english/method/internal/find_graphics_queue_family.inl"
