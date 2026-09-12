namespace Gnik_luos {
    void Vulkan::create_instance(Vulkan_info& vulkan_info) {
        if (instance != vk::raii::Instance{nullptr}) {
            throw std::runtime_error("Vulkan::create_instance => The instance has been created");
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

        #ifndef NDEBUG
            create_debug_messenger(vulkan_info);
        #endif

        vk::InstanceCreateInfo create_info;
        create_info.setPApplicationInfo(&application_info);
        create_info.setEnabledExtensionCount(static_cast<uint32_t>(vulkan_info.extension.size()));
        create_info.setPpEnabledExtensionNames(vulkan_info.extension.data());
        if (!layers.empty()) {
            create_info.setEnabledLayerCount(static_cast<uint32_t>(layers.size()));
            create_info.setPpEnabledLayerNames(layers.data());
        }
        #ifndef NDEBUG
            create_info.setPNext(&debug_create_info);
        #endif

        instance = vk::raii::Instance(context, create_info);
    }
}
