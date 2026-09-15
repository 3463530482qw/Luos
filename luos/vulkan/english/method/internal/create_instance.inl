namespace Gnik_luos {
    void Vulkan::create_instance(Vulkan_info& vulkan_info) {
        if (instance != vk::raii::Instance{nullptr}) {
            throw std::runtime_error(std::string("Vulkan::create_instance => The instance has been created"));
        }
        uint32_t sdl_extension_count = 0;
        auto sdl_extensions = SDL_Vulkan_GetInstanceExtensions(&sdl_extension_count);
        if (!sdl_extensions) {
            throw std::runtime_error(std::string("Vulkan::create_instance => SDL_Vulkan_GetInstanceExtensions failed: ") + SDL_GetError());
        }
        vulkan_info.extension.insert(vulkan_info.extension.end(), sdl_extensions, sdl_extensions + sdl_extension_count);

        vk::ApplicationInfo application_info;
        application_info.setPApplicationName(vulkan_info.window_name.c_str());
        application_info.setApplicationVersion(VK_MAKE_VERSION(1, 0, 0));
        application_info.setPEngineName("Gnik Luos");
        application_info.setEngineVersion(VK_MAKE_VERSION(1, 0, 0));
        application_info.setApiVersion(vk::ApiVersion14);

        bool support_debug_utils = false;
        #ifndef NDEBUG
            support_debug_utils = create_debug_messenger(vulkan_info);
        #endif
    }
}