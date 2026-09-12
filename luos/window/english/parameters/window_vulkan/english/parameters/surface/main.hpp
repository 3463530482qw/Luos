#pragma once
namespace Gnik_luos {
    class Vulkan_surface {
        public:
            vk::SurfaceKHR surface{nullptr};
        public:
            void create(SDL_Window* window, const vk::raii::Instance& instance);
            void destroy(const vk::raii::Instance& instance);
    };
    using 火山表面 = Vulkan_surface;
}
