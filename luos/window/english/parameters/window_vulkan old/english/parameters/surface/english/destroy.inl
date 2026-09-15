namespace Gnik_luos {
    void Vulkan_surface::destroy(const vk::raii::Instance& instance) {
        if (surface == vk::SurfaceKHR{nullptr}) {
            return;
        }
        // 表面由 SDL 创建,须交给 SDL 销毁,避免与加载器的分配器不一致
        SDL_Vulkan_DestroySurface(*instance, surface, nullptr);
        surface = nullptr;
    }
}
