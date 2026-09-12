namespace Gnik_luos {
    void Vulkan_surface::create(SDL_Window* window, const vk::raii::Instance& instance) {
        VkSurfaceKHR raw_surface = VK_NULL_HANDLE;
        if (!SDL_Vulkan_CreateSurface(window, *instance, nullptr, &raw_surface)) {
            throw std::runtime_error(std::string("Vulkan_surface::create => SDL_Vulkan_CreateSurface failed: ") + SDL_GetError());
        }
        if (raw_surface == VK_NULL_HANDLE) {
            throw std::runtime_error("Vulkan_surface::create => SDL_Vulkan_CreateSurface returned VK_NULL_HANDLE");
        }
        surface = raw_surface;
    }
}
