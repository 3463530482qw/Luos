namespace Gnik_luos {
    #ifndef NDEBUG
        void Vulkan::create_debug_messenger(Vulkan_info& vulkan_info) {
            auto available_layers = context.enumerateInstanceLayerProperties();
            for (const auto& layer : available_layers) {
                if (strcmp(layer.layerName, "VK_LAYER_KHRONOS_validation") == 0) {
                    layers.push_back("VK_LAYER_KHRONOS_validation");
                    break;
                }
            }
            if (layers.empty()) {
                return;
            }
            vulkan_info.extension.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

            // 启用项必须落在成员 vector 上:局部 vector 出函数即销毁,
            // validation_features 里的指针会变成悬垂(校验层会报枚举值越界 49)
            enabled_features = collect_validation_features(vulkan_info.debug_info);
            validation_features.setEnabledValidationFeatures(enabled_features);

            debug_create_info.setMessageSeverity(vulkan_info.debug_info.severity);
            debug_create_info.setMessageType(vulkan_info.debug_info.message_type);
            debug_create_info.setPfnUserCallback(debug_message_callback);
            debug_create_info.setPUserData(nullptr);
            debug_create_info.setPNext(&validation_features);
        }
    #else
        void Vulkan::create_debug_messenger(Vulkan_info& vulkan_info) {
        }
    #endif
}
