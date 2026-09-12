#pragma once
#include "english/parameters/viewport/main.hpp"
#include "english/parameters/surface/main.hpp"
#include "english/parameters/swapchain/main.hpp"
#include "english/parameters/renderpass/main.hpp"
#include "english/parameters/framebuffer/main.hpp"
#include "english/parameters/command_pool/main.hpp"
#include "english/parameters/command_buffer/main.hpp"
#include "english/parameters/synchronization/main.hpp"
namespace Gnik_luos {
    class Window_vulkan {
        public:
            #include "english/available/variable.inl"
            #include "中文/可用/变量.inl"
        public:
            #include "english/available/function.inl"
        private:
            #include "english/available/internal/variable.inl"
        private:
            #include "english/available/internal/function.inl"
        public:
            ~Window_vulkan();
    };
}
#include "english/parameters/viewport/english/rebuild.inl"
#include "english/parameters/surface/english/create.inl"
#include "english/parameters/surface/english/destroy.inl"
#include "english/parameters/swapchain/english/reset.inl"
#include "english/parameters/swapchain/english/create.inl"
#include "english/parameters/swapchain/english/create_image_views.inl"
#include "english/parameters/renderpass/english/create.inl"
#include "english/parameters/framebuffer/english/create.inl"
#include "english/parameters/command_pool/english/create.inl"
#include "english/parameters/command_buffer/english/allocate.inl"
#include "english/parameters/command_buffer/english/begin.inl"
#include "english/parameters/command_buffer/english/begin_render_pass.inl"
#include "english/parameters/command_buffer/english/set_viewport.inl"
#include "english/parameters/command_buffer/english/end.inl"
#include "english/parameters/synchronization/english/create.inl"
#include "english/parameters/synchronization/english/wait.inl"
#include "english/find_graphics_queue_family.inl"
#include "english/initialize.inl"
#include "english/create_swapchain.inl"
#include "english/viewport_rect.inl"
#include "english/record_command_buffers.inl"
#include "english/draw_frame.inl"
#include "english/submit_frame.inl"
#include "english/rebuild.inl"
#include "english/destroy.inl"
