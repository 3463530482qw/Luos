#include "english/parameters/viewport/main.hpp"
#include "english/parameters/surface/main.hpp"
#include "english/parameters/command_pool/main.hpp"
#include "english/parameters/swapchain/main.hpp"
#include "english/parameters/renderpass/main.hpp"
#include "english/parameters/depth/main.hpp"
#include "english/parameters/framebuffer/main.hpp"
#include "english/parameters/command_buffer/main.hpp"
#include "english/parameters/synchronization/main.hpp"

#include "english/parameters/line_render/main.hpp"
namespace Gnik_luos {
    class Window_vulkan {
        public:
            #include "english/available/variable.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
            #include "english/available/internal/function.inl"
        public:
            Window_vulkan();
            ~Window_vulkan();
    };
}
#include "english/method/available/main.inl"
#include "english/method/available/init.inl"
#include "english/method/available/request_rebuild.inl"
#include "english/method/available/draw_frame.inl"
#include "english/method/available/destroy.inl"
#include "english/method/internal/find_graphics_queue_family.inl"
#include "english/method/internal/create_swapchain.inl"
#include "english/method/internal/rebuild.inl"
#include "english/method/internal/destroy_resources.inl"
#include "english/method/internal/viewport_rect.inl"
#include "english/method/internal/record_command_buffers.inl"
#include "english/method/internal/submit_frame.inl"
