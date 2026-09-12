namespace Gnik_luos {
    #ifndef NDEBUG
        VKAPI_ATTR vk::Bool32 VKAPI_CALL debug_message_callback(
            vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
            vk::DebugUtilsMessageTypeFlagsEXT message_type,
            const vk::DebugUtilsMessengerCallbackDataEXT* callback_data,
            void* user_data
        ) {
            std::cerr << "[vulkan] " << vk::to_string(severity) << " " << vk::to_string(message_type)
                      << ": " << callback_data->pMessage << std::endl;
            return vk::False;
        }
    #endif
}
