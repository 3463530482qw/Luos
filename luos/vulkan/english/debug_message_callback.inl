namespace Gnik_luos {
    #ifndef NDEBUG
        VKAPI_ATTR vk::Bool32 VKAPI_CALL debug_message_callback(
            vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
            vk::DebugUtilsMessageTypeFlagsEXT message_type,
            const vk::DebugUtilsMessengerCallbackDataEXT* callback_data,
            void* user_data
        ) {
            std::string message = std::string("[vulkan] ") + vk::to_string(severity) + " " + vk::to_string(message_type)
                                + ": " + callback_data->pMessage;
            std::cerr << message << std::endl;

            // 校验层报错直接抛出:调用点(实例/设备/交换链创建)会把它带回应用
            if (severity == vk::DebugUtilsMessageSeverityFlagBitsEXT::eError) {
                throw std::runtime_error(message);
            }
            return vk::False;
        }
    #endif
}
