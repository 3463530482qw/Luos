namespace Gnik_luos {
    void Vulkan_surface::create(SDL_Window* window, const vk::raii::Instance& instance) {
        VkSurfaceKHR raw_surface = VK_NULL_HANDLE;
        if (!SDL_Vulkan_CreateSurface(window, *instance, nullptr, &raw_surface)) {
            throw std::runtime_error(std::string("Vulkan_surface::create => SDL_Vulkan_CreateSurface failed: ") + SDL_GetError());
        }
        if (raw_surface == VK_NULL_HANDLE) {
            throw std::runtime_error("Vulkan_surface::create => SDL_Vulkan_CreateSurface returned VK_NULL_HANDLE");
        }
        // 表面由 SDL 创建,建好后交给 raii 持有:实例销毁前随窗口火山一起释放
        surface = vk::raii::SurfaceKHR(instance, raw_surface);
    }
}
