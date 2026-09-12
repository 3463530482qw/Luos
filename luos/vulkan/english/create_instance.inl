namespace Gnik_luos {
    void Vulkan::create_instance(Vulkan_info& vulkan_info) {
        vk::ApplicationInfo app_info = vk::ApplicationInfo()
            .setPApplicationName(vulkan_info.window_name.c_str())
            .setApplicationVersion(VK_MAKE_VERSION(1, 0, 0))
            .setPEngineName("Gnik Luos")
            .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
            .setApiVersion(VK_API_VERSION_1_4);
        uint32_t sdl_extra_count = 0;
        auto* sdl_extras = SDL_Vulkan_GetInstanceExtensions(&sdl_extra_count);
        if (! sdl_extras) {
            throw std::runtime_error(std::string("Vulkan::create_instance => SDL_Vulkan_GetInstanceExtensions failed"));
        }
        std::vector<const char*> layers;
    }
}